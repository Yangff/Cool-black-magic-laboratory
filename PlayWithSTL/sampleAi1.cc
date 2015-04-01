#include "sdk.h"
#include<ctime>

const Pos EMPTYPOS = Pos(), DEFAULFPOS = Pos(75, 75);
const int EMPTYID = 0, HIGHLEVEL = 6, MAXLEVEL = 10, MAXID = 100;

static int fixId[MAXID];
static Pos fixPos[MAXID];
static bool towerDes[2];
typedef vector<const PUnit*> PUnits;
PUnits ours, others, nearBy;
static vector<Pos> blocks;

const PMap* MAP;
const PPlayerInfo* INFO;

const PUnit* belongs(int id, PUnits& units) //找出unit组成的vector中包含指定id的unit
{
    for (int i=0;i<units.size();++i)
        if (units[i]->id == id)
            return units[i];
    return NULL;
}

int unitEvaluation(string name) //评估一个单位的战斗力
{
    if (name == string("Dog") || name == string("Bow"))
        return 0;
    if (name == string("Fighter") || name == string("Assassin") || name == string("Archer")) //鼓励与敌方单位交战
        return 0;
    if (name == string("Wolf") || name == string("StoneMan"))
        return 4;
    if (name == string("Tower") || name == string("Dragon") || name == string("Roshan"))
        return HIGHLEVEL;
    return MAXLEVEL;
}

void fighting(const PUnit* a, const PUnit* b, PCommand &cmd) //单位a对单位b发起进攻
{
    Operation op;
    op.id = a->id;

    vector<const PSkill*> useSkill;
    for (int i = 0; i < a->skills.size(); ++i)
    {
        const PSkill* ptr = &a->skills[i];
        if (ptr->isHeroSkill() && a->canUseSkill(ptr->typeId))
        {
            PUnits ptr_foe;
            infectedBySkill(*INFO, a->id, ptr->typeId, ptr_foe); //寻找可用技能
            if (belongs(b->id, ptr_foe) || !strcmp(ptr->name,"Hide") || !strcmp(ptr->name,"PowerUp"))
                useSkill.push_back(ptr);
        }
    }
    if (useSkill.size()) //策略：优先使用技能
    {
        const PSkill* ptr = useSkill[rand()%useSkill.size()];
        op.type = ptr->name;
        if (ptr->needTarget())
            op.targets.push_back(b->pos);
    } else
        if (dis2(a->pos, b->pos) <= a->range) //判断单位b是否在攻击范围内
        {
            op.type = "Attack";
            op.targets.push_back(b->pos);
        } else
        {
            op.type = "Move";
            findShortestPath(*MAP, a->pos, b->pos, blocks, op.targets);
        }
    cmd.cmds.push_back(op);
}

void levelUp(const PUnit* a, PCommand &cmd) //单位a升级操作
{
    vector<string> level_ups;
    level_ups.push_back("YellowPoint");
    for (int i = 0; i < a->skills.size(); ++i)
    {
        const PSkill* ptr = &a->skills[i];
        if (ptr->isLU() && a->canUseSkill(ptr->typeId)) //选择可以升级的技能
            level_ups.push_back(ptr->name);
    }
    Operation op;
    op.id = a->id;
    op.type = level_ups[rand()%level_ups.size()]; //随机升级技能
    cmd.cmds.push_back(op);
}

void getFoes(vector<Pos> &atk_tar, int l, int u) //根据等级寻找地图中相应
{
    int t = unitEvaluation("Tower");
    if (l <= t && t <= u)
    {
        const Pos* tower = INFO->camp ? Player0_tower_pos : Player1_tower_pos;
        for (int i = 0; i < 2; ++i)
            if (!towerDes[i])
            {
                for (int j = 0; j < 5; ++j)
                    atk_tar.push_back(tower[i]); //加大推塔概率
            }
    }
    t = unitEvaluation("Dragon");
    if (l <= t && t <= u)
    {
        for (int i = 0; i < 2; ++i)
            atk_tar.push_back(Dragon_pos[i]);
        atk_tar.push_back(Roshan_pos[0]);
    }
    t = unitEvaluation("Wolf");
    if (l <= t && t <= u)
    {
        for (int i = 0; i < 4; ++i)
            atk_tar.push_back(Wolf_pos[i]);
        for (int i = 0; i < 2; ++i)
            atk_tar.push_back(StoneMan_pos[i]);
    }
    t = unitEvaluation("Dog");
    if (l <= t && t <= u)
    {
        for (int i = 0; i < 6; ++i)
            atk_tar.push_back(Dog_pos[i]);
        for (int i = 0; i < 6; ++i)
            if (i % 3) //去除两个无法移动到达的野怪
                atk_tar.push_back(Bow_pos[i]);
    }
}

void findFoes(const PUnit* a, PCommand &cmd) //单位a寻找对手
{
    if ((*a)["Exp"]->val[3]) //优先升级技能
    {
        levelUp(a, cmd);
    } else
    {
        if (fixPos[a->id] == EMPTYPOS)
        {
            vector<Pos> atk_tar;
            atk_tar.clear();
            getFoes(atk_tar, a->level > HIGHLEVEL ? HIGHLEVEL : 0, a->level); //策略：达到一定强度开始攻击防御塔
            if (atk_tar.size()) //寻找固定点的弱小对手
            {
                fixPos[a->id] = atk_tar[rand()%atk_tar.size()]; //锁定目标
            } else
            {
                fixPos[a->id] = DEFAULFPOS;
            }
        }
        Operation op;
        op.id = a->id;
        op.type = "Move";
        findShortestPath(*MAP, a->pos, fixPos[a->id], blocks, op.targets); //向弱小对手移动
        cmd.cmds.push_back(op);
    }
}

void chooseHero(const PPlayerInfo &info, PCommand &cmd) //第0回合选择英雄
{
    for(int i=0;i<info.units.size();++i)
    {
        Operation op;
        int r=rand()%3;
        if(r==0)
            op.type="ChooseAssassin";
        else if(r==1)
            op.type="ChooseFighter";
        else if(r==2)
            op.type="ChooseArcher";
        op.targets.clear();
        op.id=info.units[i].id;
        cmd.cmds.push_back(op); //随机选择职业
    }
}

void init() //一些参数初始化
{
    blocks.clear();
    getFoes(blocks, 0, MAXLEVEL);
    const Pos* tower = INFO->camp ? Player1_tower_pos : Player0_tower_pos;
    for (int i = 0; i < 2; ++i)
        blocks.push_back(tower[i]); //地图上固定点不可经过
    memset(fixId, EMPTYID, sizeof fixId);
    towerDes[0] = towerDes[1] = false;
    for (int i = 0; i < MAXID; ++i) fixPos[i] = EMPTYPOS;
}

void fightAlone(const PUnit* ptr, const PPlayerInfo &info, PCommand &cmd)
{
    info.findUnitInArea(ptr->pos, ptr->view, nearBy); //寻找附近的人
    fixPos[ptr->id] = EMPTYPOS;
    for (int i = 0; i < nearBy.size(); ++i)
    {
        if (unitEvaluation(nearBy[i]->name) > ptr->level ||
                nearBy[i]->camp == ptr->camp ||
                nearBy[i]->pos == Bow_pos[0] || nearBy[i]->pos == Bow_pos[3] ||
                nearBy[i]->findBuff("Reviving"))
            //删除等级过高的人，忽略友军，剔除复活者，删除不可到达的野怪
        {
            nearBy.erase(nearBy.begin()+i);
            --i;
        }
    }
    if (nearBy.size()) //策略：若周边有弱小对手则进行攻击
    {
        const PUnit* ptr_foe = fixId[ptr->id]!=EMPTYID ?
                    belongs(fixId[ptr->id], nearBy) : NULL; //判断之前是否锁定过目标
        if (!ptr_foe)
        {
            ptr_foe = nearBy[rand()%nearBy.size()];
            fixId[ptr->id] = ptr_foe->id; //若之前未锁定过目标，随机选定目标
        }
        fighting(ptr, ptr_foe, cmd); //与目标打斗
    } else
    {
        findFoes(ptr, cmd); //若附近没有敌军，在地图中寻找一个
    }
}

void player_ai(const PMap &map, const PPlayerInfo &info, PCommand &cmd)
{
    srand(time(0)); //随机开关打开
    cmd.cmds.clear();
    MAP = &map;
    INFO = &info;
    if (info.round == 0)
    {
        chooseHero(info, cmd); //第0回合选择英雄
        init(); //一些参数初始化
    } else //正式回合
    {
        info.findUnitByPlayer(info.player, ours); //寻找所有本方单位
        for (int i=0; i<ours.size(); ++i) //所有己方单位
        {
            const PUnit* ptr = ours[i];
            if (ptr->isHero()) //ptr是一个英雄，不和队友配合，单独作战
            {
                const Pos* tower = INFO->camp ? Player0_tower_pos : Player1_tower_pos;
                for (int i = 0; i < 2; ++i)
                    if (dis2(ptr->pos, tower[i]) < 100 && !info.findUnitByPos(tower[i]))
                        towerDes[i] = true; //去除已摧毁防御塔
                fightAlone(ptr, info, cmd);
            }
        }
    }
}
