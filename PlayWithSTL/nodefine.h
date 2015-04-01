/* goes from sdk.h und const.h */
namespace _{
struct Pos//整数坐标
{
    int x,y;
        Pos(int X=-1,int Y=-1):
        x(X),y(Y)
    {
    }
    //Pos||DPos可用函数String2Pos||String2DPos转化为字符串……
};
struct DPos//浮点数坐标
{
    double x,y;
        DPos(double X=-1,double Y=-1):
        x(X),y(Y)
    {
    }
    DPos(const Pos &pos):
        x(pos.x),y(pos.y)
    {
    }
};

const int dir[4][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};                                //四连通方向
const int Map_size = 151;                                                                //地图大小
const int Max_round = 1000;                                                              //最大回合数

//游戏中各种元素的名称列表，每个名称的下标即为其类型编号(typeId)
extern const string Area_name[];
extern const string Args_name[];
extern const string Buff_name[];
extern const string Flight_name[];
extern const string Skill_name[];
extern const char* Unit_name[];
extern const string Operation_name[];

//名称列表大小
static const int Area_name_size = 1;
static const int Args_name_size = 10;
static const int Buff_name_size = 8;
static const int Flight_name_size = 2;
static const int Skill_name_size = 23;
static const int Unit_name_size = 12;
static const int Operation_name_size = 25;

//所有特殊单位和野怪的位置
static const Pos Player0_tower_pos[] = {Pos(75, 116), Pos(116, 75)};
static const Pos Player0_spring_pos[] = {Pos(5, 145)};
static const Pos Player0_chooser_pos[] = {Pos(0, 0), Pos(2, 0), Pos(4, 0), Pos(6, 0), Pos(8, 0)};
static const Pos Player0_hero_initial_pos[] = {Pos(6, 144), Pos(4, 144), Pos(6, 146), Pos(6, 142), Pos(8, 144)};
static const Pos Player1_tower_pos[] = {Pos(75, 34), Pos(34, 75)};
static const Pos Player1_spring_pos[] = {Pos(145, 5)};
static const Pos Player1_chooser_pos[] = {Pos(0, 100), Pos(2, 100), Pos(4, 100), Pos(6, 100), Pos(8, 100)};
static const Pos Player1_hero_initial_pos[] = {Pos(144, 6), Pos(146, 6), Pos(144, 4), Pos(144, 8), Pos(142, 6)};
static const Pos Dog_pos[] = {Pos(8, 34), Pos(34, 34), Pos(54, 8), Pos(54, 75), Pos(142, 116), Pos(116, 116), Pos(96, 142), Pos(96, 75)};
static const Pos Bow_pos[] = {Pos(8, 102), Pos(54, 54), Pos(54, 115), Pos(142, 58), Pos(96, 96), Pos(96, 35)};
static const Pos Wolf_pos[] = {Pos(34, 54), Pos(56, 34), Pos(116, 96), Pos(94, 116)};
static const Pos StoneMan_pos[] = {Pos(32, 95), Pos(118, 55)};
static const Pos Dragon_pos[] = {Pos(5, 5), Pos(145, 145)};
static const Pos Roshan_pos[] = {Pos(75, 75)};

//单位属性参数
static const int Fighter_base_hp = 350;
static const int Fighter_mp = 200;
static const int Fighter_base_atk = 30;
static const int Fighter_base_def = 10;
static const int Fighter_speed = 12;
static const int Fighter_range = 8;
static const int Fighter_view = 144;
static const int Fighter_hp_delta = 35;
static const int Fighter_atk_delta = 4;
static const int Fighter_def_delta = 3;
static const int Fighter_attack_maxcd = 2;
static const int Archer_base_hp = 250;
static const int Archer_mp = 200;
static const int Archer_base_atk = 32;
static const int Archer_base_def = 5;
static const int Archer_speed = 25;
static const int Archer_range = 81;
static const int Archer_view = 144;
static const int Archer_hp_delta = 25;
static const int Archer_atk_delta = 5;
static const int Archer_def_delta = 2;
static const int Archer_attack_maxcd = 2;
static const int Assassin_base_hp = 200;
static const int Assassin_mp = 200;
static const int Assassin_base_atk = 27;
static const int Assassin_base_def = 3;
static const int Assassin_speed = 20;
static const int Assassin_range = 5;
static const int Assassin_view = 144;
static const int Assassin_hp_delta = 20;
static const int Assassin_atk_delta = 6;
static const int Assassin_def_delta = 2;
static const int Assassin_attack_maxcd = 1;
static const int Tower_hp = 1000;
static const int Tower_atk = 55;
static const int Tower_def = 15;
static const int Tower_range = 100;
static const int Tower_view = 144;
static const int Tower_attack_maxcd = 1;
static const int Spring_hp = 2000;
static const int Spring_atk = 100;
static const int Spring_def = 0;
static const int Spring_range = 50;
static const int Spring_view = 144;
static const int Spring_attack_maxcd = 1;
static const int Dog_hp = 250;
static const int Dog_atk = 25;
static const int Dog_def = 10;
static const int Dog_speed = 16;
static const int Dog_range = 9;
static const int Dog_view = 144;
static const int Dog_attack_maxcd = 2;
static const int Dog_exp = 70;
static const int Dog_reviving_time = 20;
static const int Bow_hp = 280;
static const int Bow_atk = 35;
static const int Bow_def = 0;
static const int Bow_speed = 16;
static const int Bow_range = 81;
static const int Bow_view = 144;
static const int Bow_attack_maxcd = 2;
static const int Bow_exp = 90;
static const int Bow_reviving_time = 20;
static const int Wolf_hp = 350;
static const int Wolf_atk = 42;
static const int Wolf_def = 12;
static const int Wolf_speed = 16;
static const int Wolf_range = 9;
static const int Wolf_view = 144;
static const int Wolf_attack_maxcd = 1;
static const int Wolf_exp = 150;
static const int Wolf_reviving_time = 25;
static const int StoneMan_hp = 550;
static const int StoneMan_atk = 35;
static const int StoneMan_def = 25;
static const int StoneMan_speed = 12;
static const int StoneMan_range = 9;
static const int StoneMan_view = 144;
static const int StoneMan_attack_maxcd = 2;
static const int StoneMan_exp = 150;
static const int StoneMan_reviving_time = 25;
static const int Dragon_hp = 600;
static const int Dragon_atk = 80;
static const int Dragon_def = 10;
static const int Dragon_speed = 12;
static const int Dragon_range = 81;
static const int Dragon_view = 144;
static const int Dragon_attack_maxcd = 2;
static const int Dragon_exp = 500;
static const int Dragon_reviving_time = 60;
static const int Roshan_hp = 1200;
static const int Roshan_atk = 65;
static const int Roshan_def = 25;
static const int Roshan_speed = 12;
static const int Roshan_range = 9;
static const int Roshan_view = 144;
static const int Roshan_attack_maxcd = 2;
static const int Roshan_exp = 500;
static const int Roshan_reviving_time = 80;

static const double Hp_recover_rate = 0.01;                                               //生命值回复速度
static const double Mp_recover_rate = 0.01;                                               //魔法值回复速度
//static const int Skill_maxcd = 2;                                                       

//技能参数
static const int Charge_range = 64;
static const int Charge_dizzy_time[] = {2, 3, 4};
static const int Charge_damage[] = {30, 60, 90};
static const int Charge_mp = 50;
static const int Charge_maxcd = 12;
static const int Spin_range = 13;
static const int Spin_damage[] = {45, 90, 135};
static const int Spin_mp = 70;
static const int Spin_maxcd = 8;
static const int Yell_range = 13;
static const int Yell_def_delta[] = {5, 10, 15};
static const int Yelled_time[] = {3, 4, 5};
static const int Yell_mp = 30;
static const int Yell_maxcd = 15;
static const int PiercingArrow_range = 81;
static const int PiercingArrow_damage[] = {45, 100, 155};
static const int PiercingArrow_mp = 70;
static const int PiercingArrow_maxcd = 12;
static const int SignalArrow_range = 100;
static const int RainyPlace_range = 6;
static const double Rainy_speed_delta_rate = -0.4375; //减速25%，Rainy_speed_delta_rate=sqrt(0.75)-1
static const int Rainy_damage[] = {15, 30, 45};
static const int Rainy_time = 5;
static const int ArrowsRain_mp = 70;
static const int ArrowsRain_maxcd = 24;
static const int ArrowsRain_range = 100;
static const int PowerUp_atk_delta[] = {12, 24, 36};
static const int Striking_time = 12;
static const int PowerUp_mp = 100;
static const int PowerUp_maxcd = 25;
static const int Hided_time = 9;
static const double Hided_speed_delta_rate[] = {1.0, 1.5, 2.0}; //加速41.4%，58.1%，73.2%，同上
static const int Hided_atk_delta[] = {30, 45, 60};
static const int Hided_mp = 50;
static const int Hided_maxcd = 20;
static const int FlyingBlade_range = 81;
static const int FlightBlade_damage[] = {45, 100, 155};
static const double Slow_speed_delta_rate = -0.75; //减速50%，同上
static const int Slow_time = 4;
static const int FlyingBlade_mp = 75;
static const int FlyingBlade_maxcd = 12;
static const int Blink_range = 81;
static const int Blink_mp[] = {50, 25, 0};
static const int Blink_maxcd[] = {12, 8, 5};
static const int YellowPoint_hp_delta = 10;
static const int YellowPoint_atk_delta = 2;
static const int YellowPoint_def_delta = 2;
static const int LifeSpring_range = 81;
static const int LifeSpring_hp_recover_delta = 50;
static const int LifeSpring_mp_recover_delta = 30;

//飞行道具速度
static const int FlightBlade_speed = 64;
static const int SignalArrow_speed = 64;

//其它参数
static const int Move_height_delta = 1;                                                         //移动高度差限制
static const int Archer_attack_height_delta = 2;                                                //弓手普通攻击高度差限制（超过此限制伤害减半）
static const int Attack_min_damage = 5;                                                         //普通攻击最低伤害值
static const double Exp_share_rate = 0.5;                                                       //周围单位分享的经验值比例
static const int Exp_share_range = 100;                                                         //分享经验值范围
static const int Hero_initial_level = 0;                                                        //英雄初始等级
static const int Hero_max_level = 9;                                                            //英雄最高等级
static const int Skill_initial_level = -1;                                                      //英雄技能初始等级（未分配技能点）
static const int Skill_max_level = 2;         
struct PMap//地图
{
    vector<int> playerIds;//玩家编号列表（默认0、1为游戏双方，2为野怪）
    int height[Map_size][Map_size];//地图中各个点的高度
};
struct PFlight//飞行道具
{
    int typeId;//类型编号，与名称的对应关系详见Flight_name[]
    char name[100];//名称
    int id;//编号
    int unitId;//来源的单位编号
    int camp;//所属阵营
    int speed;//速度
    Pos pos;//位置
    Pos target;//目标位置
};
struct PArea//（作用）范围
{
    int typeId;//类型编号，与名称的对应关系详见Area_name[]
    char name[100];//名称
    int id;//编号
    int camp;//所属阵营
    int timeLeft;//剩余时间
    Pos center;//圆心坐标
    int radius;//半径
    bool containPos(Pos _) const;//求区域内是否包含某个点_
    bool containDPos(DPos _, double zero = 1e-10) const;//求区域内是否包含某个点_，zero表示精度（下溢值）
};
struct PArg//各种参数（属性等）
{
    int typeId;//类型编号，与名称的对应关系详见Args_name[]
    char name[100];//名称
    std::vector<int> val;//参数列表，各个下标的意义见游戏规则说明
};
struct PBuff//状态
{
    int typeId;//类型编号，与名称的对应关系详见Buff_name[]
    char name[100];//名称
    int level;//等级
    int timeLeft;//剩余时间
    PBuff(int _typeId, int _level, int _timeLeft);
    bool isPositive() const;//判断是否为对自己有利的状态
};
struct PSkill//技能
{
    int typeId;//类型编号，与名称的对应关系详见Skill_name[]
    char name[100];//名称
    int mp;//所需魔法
    int level;//等级
    int maxLevel;//等级上限
    int cd;//目前剩余cd时间
    int maxCd;//总cd时间，对于普通攻击（Attack）即为攻速

};
struct PUnit//单位
{
    int typeId;//类型编号，与名称的对应关系详见Unit_name[]
    char name[100];//名称
    int id;//编号
    int player;//所属玩家编号
    int camp;//所属阵营
    Pos pos;//位置
    std::vector<PArg> args;//单位参数列表
    std::vector<PBuff> buffs;//单位状态列表
    std::vector<PSkill> skills;//单位技能列表
    //以下均为目前的属性值，供简便调用
    int hp;//生命值
    int mp;//魔法值
    int atk;//攻击
    int def;//防御
    int speed;//速度
    int exp;//经验值
    int range;//射程
    int view;//视野
    int level;//等级
    
};
struct PPlayerInfo//作为传入参数的局面信息
{
    int round;//目前回合
    int player;//你的玩家编号
    int camp;//你的玩家所属阵营
    std::vector<PUnit> units;//可见的单位列表
    std::vector<PFlight> flights;//可见的飞行道具列表
    std::vector<PArea> areas;//可见的作用范围列表
    PPlayerInfo(int _round = 0, int _player = 0, int _camp = 0):  round(_round), player(_player), camp(_camp)
    {
        units.clear() ;
        flights.clear();
        areas.clear();
    }
};
struct Operation//操作
{
    int id;//实施者编号
    int typeId;//类型编号，与名称的对应关系详见Operation_name[]
    std::string type;//操作名称
    vector<Pos> targets;//目标位置列表，注：除移动（"Move"）外的操作，该列表的长度不大于1
    Operation(): id(-1),typeId(-1),type("Stop") //默认不动
    {
        targets.clear();
    }
};
/* remove function define */
};