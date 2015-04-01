#include "sdk.h"
using namespace std;
#define FOE (otherUnit->id > 15 && otherUnit->camp != info->camp)
typedef const PMap CM;
typedef const PPlayerInfo CP;
typedef const PUnit CU;
typedef const PArg CA;
const int ma = 100; //MAXID
const int nearBy=8; //附近单位增加仇恨
const int maxDis0=324; //离出生点的最远距离
const int maxDis1=144; //离当前位置的最远距离

// define and typedef

CP* info;
CM* ditu;
PCommand* cmd;

static Pos poso[ma];
static int ang[ma][ma];
Pos pos[ma];
bool seen[ma], atk;
int c[ma], d[ma];
int rd;
int *angP;
vector<Pos> nu;
vector<CU*> ourUnits;

bool comp(int a,int b);
void calAng();
bool calYell(CU*);

// extern funcs and vars

void player_ai(const PMap &ditu_, const PPlayerInfo &info_, PCommand &cmd_)
{
    info = &info_;
    ditu = &ditu_;
    cmd = &cmd_;
    cmd->cmds.clear();
    nu.clear();
    info->findUnitByPlayer(info->player, ourUnits);

    if (info->round == 0)
    {
        for (int i = 0; i < ourUnits.size(); ++i)
        {
            poso[ourUnits[i]->id] = pos[ourUnits[i]->id] = ourUnits[i]->pos;
        }
        memset(ang, 0, sizeof ang); //野怪记录出生地点，重置仇恨值
    } else
    {
        calAng(); //计算每个野怪对每个敌人的仇恨值

        for (int i = 0; i < ourUnits.size(); ++i)
        {
            int id = ourUnits[i]->id;
            bool flag = true;
            atk = true;
            angP = ang[id];

            if (calYell(ourUnits[i])) continue; //处理野怪被嘲讽的情况

            for (int j = 0; j < ma; ++j) c[j] = d[j] = j;
            random_shuffle(d,d+ma);
            sort(c,c+ma,comp); //对仇恨排序，仇恨相同顺序随机

            Operation op;
            op.id = id;

            for (int j = 0; j < ma; ++j)
            {
                if (angP[c[j]] == 0 || !flag) break;
                CU* otherUnit = info->findUnitById(c[j]);

                if (otherUnit && FOE)
                {
                    Pos ps = otherUnit->pos;
                    if (dis2(ps,pos[id])<=maxDis1 && dis2(ps,poso[id])<=maxDis0)
                        //离自己距离太远或离出生点太远放弃目标
                    {
                        if (dis2(ps,pos[id])<=ourUnits[i]->range && atk)
                            //攻击范围内直接攻击，否则移动
                        {
                            angP[id] += 1;
                            op.type = "Attack";
                            op.targets.push_back(ps);
                        } else
                        {
                            op.type = "Move";
                            findShortestPath(*ditu, pos[id], ps, nu, op.targets);
                        }
                        flag = false;
                    }
                }
            }

            if (flag && pos[id] != poso[id])
                //若无事可做，回到出生点
            {
                op.type = "Move";
                findShortestPath(*ditu, pos[id], poso[id], nu, op.targets);
            }

            cmd->cmds.push_back(op);
        }
    }
}

bool comp(int a,int b)
{
    return angP[a]>angP[b] || (angP[a]==angP[b] && d[a]<d[b]);
}

void calAng() //改变仇恨值，仇恨值累计
{
    memset(seen, false, sizeof seen);
    for (int i = 0; i < ourUnits.size(); ++i)
    {
        pos[ourUnits[i]->id] = ourUnits[i]->pos;
        CA* arg = (*ourUnits[i])["LastHit"];
        if (arg)
        {
            for(int j=0; j<ma && j<arg->val.size(); ++j)
                if (arg->val[j] >= info->round-1)
                    ang[ourUnits[i]->id][j] += 5; //攻击自己的单位仇恨值+5
        }
    }
    for (int i = 0; i < info->units.size(); ++i)
    {
        CU* otherUnit = &info->units[i];
        if (FOE)
        {
            seen[otherUnit->id] = true;
            for (int j = 0; j < ourUnits.size(); ++j)
            {
                if (dis2(otherUnit->pos,ourUnits[j]->pos) <= nearBy)
                    ang[ourUnits[j]->id][otherUnit->id] += 1; //附近敌人仇恨值+1
                if (dis2(otherUnit->pos,ourUnits[j]->pos) > maxDis0)
                    ang[ourUnits[j]->id][otherUnit->id] = 0; //消除对远处敌人的视野
            }
        }
    }
    for (int i = 0; i < ourUnits.size(); ++i)
    {
        for (int j = 0; j < ma; ++j)
        {
            if (!seen[j])
                ang[ourUnits[i]->id][j] = 0; //消除不可见单位的仇恨值
        }
    }
    // 计算仇恨值
}

bool calYell(CU* ourUnit)
{
    int id = ourUnit->id;
    CA* arg = (*ourUnit)["OnlyTarget"];
    if (arg)
    {
        int id2 = arg->val[0];
        angP[id] += 1; //嘲讽单位仇恨值+1
        if (id2 != -1)
        {
            CU* otherUnit = info->findUnitById(id2);
            if (otherUnit)
            {
                Pos ps = otherUnit->pos;
                if (dis2(ps,pos[id])<=ourUnit->range) //若该单位在攻击范围内，攻击之
                {
                    Operation op;
                    op.id = id;
                    angP[id] += 1;
                    op.targets.push_back(ps);
                    cmd->cmds.push_back(op);
                    return true;
                }
            }
            atk = false;
        }
    }
    return false;
}
