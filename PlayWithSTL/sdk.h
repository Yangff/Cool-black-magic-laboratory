#ifndef AI9_2015_H
#define AI9_2015_H

#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#ifndef POS_H
#define POS_H

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
int crossProduct(Pos A,Pos B,Pos C);//向量AB叉乘AC
bool cross(Pos A,Pos B,Pos C,Pos D);//判断线段AB与CD是否有公共点
bool checkOnLine(Pos A,Pos B,Pos C);//判断AB连线是否与C（方格）有交点
int dis2(Pos A,Pos B);//欧氏距离平方
double dis(Pos A,Pos B);//欧几里得距离
bool operator==(Pos A,Pos B);//相等
bool operator!=(Pos A,Pos B);//不等
Pos operator+(Pos A,Pos B);//加法
Pos operator-(Pos A,Pos B);//减法
Pos operator*(Pos A,int _);//数乘
Pos operator*(int _,Pos A);//数乘
//以下面对DPos定义的函数其功能与面对Pos的同名函数相同
double crossProduct(DPos A,DPos B,DPos C);
bool cross(DPos A,DPos B,DPos C,DPos D);
bool checkOnLine(DPos A,DPos B,DPos C);
double dis2(DPos A,DPos B);
double dis(DPos A,DPos B);
bool operator==(DPos A,DPos B);
bool operator!=(DPos A,DPos B);
DPos operator+(DPos A,DPos B);
DPos operator-(DPos A,DPos B);
DPos operator*(DPos A,double _);
DPos operator*(double _,DPos A);
#endif//POS_H

#include "const.h"
struct PMap//地图
{
    vector<int> playerIds;//玩家编号列表（默认0、1为游戏双方，2为野怪）
    int height[Map_size][Map_size];//地图中各个点的高度
    PMap(const char* fileName);//读入地图信息
    PMap()
    {
        playerIds.clear();
    }
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
    PFlight(int _typeId, int _id, int _unitId, int _camp, int _speed, int _pos_x, int _pos_y, int _target_x, int _target_y);
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
    PArea(int _typeId, int _id, int _camp, int _timeLeft, int _center_x, int _center_y, int _radius);
    bool containPos(Pos _) const;//求区域内是否包含某个点_
    bool containDPos(DPos _, double zero = 1e-10) const;//求区域内是否包含某个点_，zero表示精度（下溢值）
};
struct PArg//各种参数（属性等）
{
    int typeId;//类型编号，与名称的对应关系详见Args_name[]
    char name[100];//名称
    std::vector<int> val;//参数列表，各个下标的意义见游戏规则说明
    PArg(int _typeId);
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
    PSkill(int _typeId, int _mp, int _level, int _maxLevel, int _cd, int _maxCd);
    bool isLU() const;//判断技能是否为升级类技能（不含黄点）
    bool isHeroSkill() const;//判断技能是否为英雄技能（不含升级类技能）
    bool needTarget() const;//判断技能是否需要指定坐标
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
    PUnit(int _typeId, int _id, int _player, int _camp, int _pos_x, int _pos_y);
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
    
    bool isHero() const;//判断单位是否为英雄
    bool isWild() const;//判断单位是否为野怪
    const PArg* operator[] (int _typeId) const;//按类型编号查询参数
    const PArg* operator[] (string _) const;//按名称查询参数
    const PBuff* findBuff(int _typeId) const;//按类型编号查询状态
    const PBuff* findBuff(string _) const;//按名称查询状态
    const PSkill* findSkill(int _typeId) const;//按类型编号查询技能
    const PSkill* findSkill(string _) const;//按名称查询技能
    bool canMove() const;//判断单位目前是否可以移动
    bool canUseSkill(int _typeId) const;//判断指定单位目前是否可以使用某种技能，_typeId为技能类型编号
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
    
    const PUnit* findUnitById(int _id) const;//返回编号为_id的单位
    const PUnit* findUnitByPos(Pos _pos) const;//返回位置为_pos的单位
    void findUnitByTypeId(int _typeId, std::vector<const PUnit*> &_unitList) const;//返回所有类型编号为_typeId的单位列表_unitList
    void findUnitByName(string _name, std::vector<const PUnit*> &_unitList) const;//返回所有名称为_name的单位列表_unitList
    void findUnitByPlayer(int _player, std::vector<const PUnit*> &_unitList) const;//返回所有属于玩家_player的单位列表_unitList
    void findUnitInArea(Pos _, int _range, std::vector<const PUnit*> &_unitList) const;//返回到点_的距离不超过_range的单位列表_unitList
    const PFlight* findFlightById(int _id) const;//返回编号为_id的飞行道具
    void findFlightByTypeId(int _typeId, std::vector<const PFlight*> &_flightList) const;//返回所有类型编号为_typeId的飞行道具列表_flightList
    void findFlightByName(string _name, std::vector<const PFlight*> &_flightList) const;//返回所有名称为_name的飞行道具列表_flightList
    void findFlightByPlayer(int _player, std::vector<const PFlight*> &_flightList) const;//返回所有属于玩家_player的飞行道具列表_flightList
    const PArea* findAreaById(int _id) const;//返回编号为_id的作用范围
    void findAreaByCenterPos(Pos _center, std::vector<const PArea*> &_areaList) const;//返回所有圆心坐标为_center的作用范围列表_areaList
    void findAreaByTypeId(int _typeId, std::vector<const PArea*> &_areaList) const;//返回所有类型编号为_typeId的作用范围列表_areaList
    void findAreaByName(string _name, std::vector<const PArea*> &_areaList) const;//返回所有名称为_name的作用范围列表_areaList
    void findAreaByCamp(int _camp, std::vector<const PArea*> &_areaList) const;//返回所有属于阵营_camp的作用范围列表_areaList
};
#ifndef _AI__
#include "../PCommand/Operation.h"
#include "../PCommand/PCommand.h"
#else
#ifndef OPERATION_H
#define OPERATION_H
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
    Operation(const Operation &_);//给出typeId和type的其中之一即可，默认为typeId
};
#endif//OPERATION_H
#ifndef PCOMMAND_H
#define PCOMMAND_H
struct PCommand//玩家给出的行动列表
{
    std::vector<Operation> cmds;
    PCommand()
    {
        cmds.clear();
    }
};
#endif//PCOMMAND_H
#endif//_AI__

bool checkPos(Pos A);
//判断坐标是否在地图内
void findShortestPath(const PMap &map, Pos start, Pos dest, std::vector<Pos> &_path);
//寻路，返回从位置start到dest的一条最短路径，考虑悬崖，不考虑其它单位，若路径不存在返回一个负数坐标
void findShortestPath(const PMap &map, Pos start, Pos dest, const std::vector<Pos> &blocks, std::vector<Pos> &_path);
//带卡位的寻路，返回从位置start到dest的一条最短路径，blocks中的位置不可经过，考虑悬崖，若路径不存在返回一个负数坐标

void findShortestPathWithSymbols(const PMap &map, const std::vector<Pos> &symbols, std::vector<Pos> &_path);
//带标志点寻路，返回经过symbols内所有位置的一条最短路径（symbols的首尾元素表示起、终点），考虑悬崖，不考虑其它单位，若路径不存在返回一个负数坐标
void findShortestPathWithSymbols(const PMap &map, const std::vector<Pos> &symbols, const std::vector<Pos> &blocks, std::vector<Pos> &_path);
//带卡位和标志点的寻路，返回经过symbols内所有位置的一条最短路径（symbols的首尾元素表示起、终点），blocks中的位置不可经过，考虑悬崖，若路径不存在返回一个负数坐标

void infectedBySkill(const PPlayerInfo &info, int _unitId, int _typeId, std::vector<const PUnit*> &_unitList);
//返回编号为_unitId的单位目前使用某种技能可能影响到（即在射程内）的单位列表_unitList，_typeId为技能类型编号

/* following code should write in host program */

#ifndef _AI__

/* !!WARN: it's not binary safe version */

const size_t sizes[] = {
    sizeof(std::string),
    sizeof(std::vector<int>),
    sizeof(std::vector<PArg>),
    sizeof(std::vector<PBuff>),
    sizeof(std::vector<PSkill>),
    sizeof(std::vector<PUnit>),
    sizeof(std::vector<PFlight>),
    sizeof(std::vector<PArea>),
    sizeof(std::vector<Operation>),
};
#include <vector>
#include <string>
#include <cstdio>

namespace _{

    const char * GetString(std::string * _){
        return _->c_str();
    }

    template<class T>
    static size_t SizeVector(std::vector<T> *_){
        return _->size();
    }

    template<class T>
    static void PushVector(std::vector<T> *_, T &v){
        _->push_back(v);
    }

    template<class T>
    static T AtVector(std::vector<T> *_, int i){
        return _->at(i);
    }

};
#define getVector(type) \
{(void*)_::SizeVector<type>, (void*)_::PushVector<type>, (void*)_::AtVector<type>}

void makeFuncTable(){
    const void * functable[][3] = {
        /* string */
        {(void*)_::GetString,NULL,NULL},
        getVector(int),
        getVector(PArg),
        getVector(PBuff),
        getVector(PSkill),
        getVector(PUnit),
        getVector(PFlight),
        getVector(PArea),
        getVector(Operation),
    };
    /* TODO: call ai's initWarpper(sizes, functable) */
}

#endif

#ifdef _AI__
#include "stdconst.h"

extern "C" void initWarpper(size_t *sizes, void * functable[][5]);

#endif
extern "C" void player_ai(fake::PMap *map,fake::PPlayerInfo *info,fake::PCommand *cmd);
#ifdef _AI__
#define player_ai player_ai_1
void player_ai(const PMap &map,const PPlayerInfo &info,PCommand &cmd);
#endif//AI9_2015_H
