//本文件包含游戏中可能用到的所有常数

#ifndef CONST_H
#define CONST_H

#include "sdk.h"
#include <string>
#include <vector>
using namespace std;

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
static const int Skill_max_level = 2;                                                           //英雄技能最高等级
Pos unitTarget(Pos start, Pos drct, int _speed, int _timeLeft);                    //返回从start发出，移动方向为drct，移动速度为_speed的单位在_timeLeft回合后的位置


//集成单位参数信息类的定义
struct UnitArgs                                                                          //单位属性参数，同时用于野怪属性参数信息
{
    int typeId;                                                                          //类型编号
    string name;                                                                         //名称
    int hp;                                                                              //生命值，在HeroArgs中表示初始生命值
    int atk;                                                                             //攻击力，在HeroArgs中表示初始攻击力
    int def;                                                                             //防御力，在HeroArgs中表示初始防御力
    int speed;                                                                           //速度（对SpecialUnitArgs无效）
    int range;                                                                           //射程
    int exp;                                                                             //死亡分配的经验值（对SpecialUnitArgs无效）
    int view;                                                                            //视野
    int attack_maxcd;                                                                    //攻速
    int reviving_time;                                                                   //复活回合数（对SpecialUnitArgs无效）
    vector<Pos> poslist;                                                                 //位置列表（对HeroArgs无效）
    
    protected:
    UnitArgs(int _typeId, int _hp, int _atk, int _def, int _speed, int _range, int _view, int _maxcd);
    
    void newPos(Pos _);                                                                   //添加位置


    public:
    UnitArgs(int _typeId, int _hp, int _atk, int _def, int _speed, int _range, int _exp, int _view, int _maxcd, int _time, const Pos* _begin, const Pos* _end);

};

struct HeroArgs: public UnitArgs                                                         //英雄属性参数信息
{
    int mp;                                                                              //魔法值
    int hp_delta;                                                                        //生命成长值
    int atk_delta;                                                                       //攻击力成长值
    int def_delta;                                                                       //防御力成长值
    
    HeroArgs(int _typeId, int _hp, int _mp, int _atk, int _def, int _speed, int _range, int _view, int _maxcd,
             int _hp_delta, int _atk_delta, int _def_delta);
    
    inline int currentLevel_hp(int _level)                                                      //返回等级为_level时的生命值
    {
        return hp + _level * hp_delta;
    }
    inline int currentLevel_atk(int _level)                                                     //返回等级为_level时的攻击力
    {
        return atk + _level * atk_delta;
    }
    inline int currentLevel_def(int _level)                                                     //返回等级为_level时的防御力
    {
        return def + _level * def_delta;
    }
    inline static int expForLevelUp(int _level)                                                 //返回从_level级升到(_level+1)级所需经验，与英雄种类无关
    {
        return 100 + _level * 25;
    }
    inline static int currentLevel_reviving_time(int _level)                                    //返回等级为_level时的复活时间，与英雄种类无关
    {
        return 5 * (_level + 1);
    }
    inline static int currentLevel_exp(int _level)                                              //返回等级为_level时的死亡分配经验值，与英雄种类无关
    {
        return 50 + _level * 50;
    }
};

struct SpecialUnitArgs: public UnitArgs                                                  //特殊单位属性参数信息
{
    int player;                                                                          //所属玩家
    
    SpecialUnitArgs(int _player, int _typeId, int _hp, int _atk, int _def, int _range, int _view, int _maxcd, const Pos* _begin, const Pos* _end);
};

//以下均为集成的单位参数信息，供某些场合简便调用

//英雄
static const HeroArgs heroes[]={
    HeroArgs(0, Fighter_base_hp, Fighter_mp, Fighter_base_atk, Fighter_base_def, Fighter_speed, Fighter_range, Fighter_view, Fighter_attack_maxcd, 
        Fighter_hp_delta, Fighter_atk_delta, Fighter_def_delta),
    HeroArgs(1, Archer_base_hp, Archer_mp, Archer_base_atk, Archer_base_def, Archer_speed, Archer_range, Archer_view, Archer_attack_maxcd, 
        Archer_hp_delta, Archer_atk_delta, Archer_def_delta),
    HeroArgs(2, Assassin_base_hp, Assassin_mp, Assassin_base_atk, Assassin_base_def, Assassin_speed, Assassin_range, Assassin_view, Assassin_attack_maxcd, 
        Assassin_hp_delta, Assassin_atk_delta, Assassin_def_delta)
};

//特殊单位
static const SpecialUnitArgs specialUnits[]={
    SpecialUnitArgs(0, 3, Tower_hp, Tower_atk, Tower_def, Tower_range, Tower_view, Tower_attack_maxcd,
        Player0_tower_pos, Player0_tower_pos + sizeof(Player0_tower_pos) / sizeof(Pos)),
    SpecialUnitArgs(1, 3, Tower_hp, Tower_atk, Tower_def, Tower_range, Tower_view, Tower_attack_maxcd,
        Player1_tower_pos, Player1_tower_pos + sizeof(Player1_tower_pos) / sizeof(Pos)),
    SpecialUnitArgs(0, 4, Spring_hp, Spring_atk, Spring_def, Spring_range, Spring_view, Spring_attack_maxcd,
        Player0_spring_pos, Player0_spring_pos + sizeof(Player0_spring_pos) / sizeof(Pos)),
    SpecialUnitArgs(1, 4, Spring_hp, Spring_atk, Spring_def, Spring_range, Spring_view, Spring_attack_maxcd,
        Player1_spring_pos, Player1_spring_pos + sizeof(Player1_spring_pos) / sizeof(Pos)),
    SpecialUnitArgs(0, 5, 0, 0, 0, 0, 0, 0, Player0_chooser_pos, Player0_chooser_pos + sizeof(Player0_chooser_pos) / sizeof(Pos)),
    SpecialUnitArgs(1, 5, 0, 0, 0, 0, 0, 0, Player1_chooser_pos, Player1_chooser_pos + sizeof(Player1_chooser_pos) / sizeof(Pos))
};

//野怪
static const UnitArgs monsters[]={
    UnitArgs(6, Dog_hp, Dog_atk, Dog_def, Dog_speed, Dog_range, Dog_exp, Dog_view, Dog_attack_maxcd, Dog_reviving_time,
        Dog_pos, Dog_pos + sizeof(Dog_pos) / sizeof(Pos)),
    UnitArgs(7, Bow_hp, Bow_atk, Bow_def, Bow_speed, Bow_range, Bow_exp, Bow_view, Bow_attack_maxcd, Bow_reviving_time,
        Bow_pos, Bow_pos + sizeof(Bow_pos) / sizeof(Pos)),
    UnitArgs(8, Wolf_hp, Wolf_atk, Wolf_def, Wolf_speed, Wolf_range, Wolf_exp, Wolf_view, Wolf_attack_maxcd, Wolf_reviving_time,
        Wolf_pos, Wolf_pos + sizeof(Wolf_pos) / sizeof(Pos)),
    UnitArgs(9, StoneMan_hp, StoneMan_atk, StoneMan_def, StoneMan_speed, StoneMan_range, StoneMan_exp, StoneMan_view, StoneMan_attack_maxcd, StoneMan_reviving_time,
        StoneMan_pos, StoneMan_pos + sizeof(StoneMan_pos) / sizeof(Pos)),
    UnitArgs(10, Dragon_hp, Dragon_atk, Dragon_def, Dragon_speed, Dragon_range, Dragon_exp, Dragon_view, Dragon_attack_maxcd, Dragon_reviving_time,
        Dragon_pos, Dragon_pos + sizeof(Dragon_pos) / sizeof(Pos)),
    UnitArgs(11, Roshan_hp, Roshan_atk, Roshan_def, Roshan_speed, Roshan_range, Roshan_exp, Roshan_view, Roshan_attack_maxcd, Roshan_reviving_time,
        Roshan_pos, Roshan_pos + sizeof(Roshan_pos) / sizeof(Pos))
};

#endif //CONST_H
