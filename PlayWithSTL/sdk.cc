/*
    !WARN!
    this version of sdk for vc (or other complier without sgi stl of probably version only)
    it may let your ai run slower any may have some unknown bugs.
    if you have any problem with this.
*/

#include "sdk.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>

static int vst[Map_size][Map_size];
static Pos Q[Map_size * Map_size + 1], Q_prior[Map_size][Map_size];
static int countF = 0;

PMap::PMap(const char *fileName)//地图
{
    playerIds.clear();
    playerIds.push_back(-1);
    playerIds.push_back(-1);
    playerIds.push_back(-1);
    
    ifstream fin(fileName);
    char ch[200];
    for(int i=0;i<Map_size;++i)
    {
        fin>>ch;
        for(int j=0;j<Map_size;++j)
            height[i][j]=ch[j]-'0';
    }
    fin.close();
}

PFlight::PFlight(int _typeId, int _id, int _unitId, int _camp, int _speed, int _pos_x, int _pos_y, int _target_x, int _target_y):
    typeId(_typeId), id(_id), unitId(_unitId), camp(_camp), speed(_speed), pos(Pos(_pos_x, _pos_y)), target(Pos(_target_x, _target_y))//飞行道具
{
    strcpy(name, Flight_name[typeId].c_str());
}

PArea::PArea(int _typeId, int _id, int _camp, int _timeLeft, int _center_x, int _center_y, int _radius):
    typeId(_typeId), id(_id), camp(_camp), timeLeft(_timeLeft), center(Pos(_center_x, _center_y)), radius(_radius)//（作用）范围
{
    strcpy(name, Area_name[typeId].c_str());
}
bool PArea::containPos(Pos _) const//求区域内是否包含某个点_
{
    return dis2(center, _) <= radius * radius;
}
bool PArea::containDPos(DPos _, double zero) const//求区域内是否包含某个点_，zero表示精度（下溢值）
{
    return dis2((DPos) center, _) + zero <= radius * radius;
}

PArg::PArg(int _typeId): typeId(_typeId)//参数
{
    strcpy(name, Args_name[typeId].c_str());
    val.clear();
}

PBuff::PBuff(int _typeId, int _level, int _timeLeft):
    typeId(_typeId), level(_level), timeLeft(_timeLeft)//状态
{
    strcpy(name, Buff_name[typeId].c_str());
}
bool PBuff::isPositive() const //判断是否为对自己有利的状态
{
    return (typeId == 0 || typeId == 3 || typeId == 5);
}

PSkill::PSkill(int _typeId, int _mp, int _level, int _maxLevel, int _cd, int _maxCd):
    typeId(_typeId), mp(_mp), level(_level), maxLevel(_maxLevel), cd(_cd), maxCd(_maxCd)//技能
{
    strcpy(name, Skill_name[typeId].c_str());
}
bool PSkill::isLU() const //判断技能是否为升级类技能（不含黄点）
{
    return (typeId >= 2 && typeId <= 18 && !(typeId & 1));
}

bool PSkill::isHeroSkill() const //判断技能是否为英雄技能（不含升级类技能）
{
    return (typeId >= 1 && typeId <= 19 && typeId & 1);
}

bool PSkill::needTarget() const //判断技能是否需要指定坐标
{
    return typeId == 0 || typeId == 1 || typeId == 7 || typeId == 9 || typeId == 15 || typeId == 17;
}

PUnit::PUnit(int _typeId, int _id, int _player, int _camp, int _pos_x, int _pos_y):
    typeId(_typeId), id(_id), player(_player), camp(_camp), pos(Pos(_pos_x, _pos_y))//单位
{
    strcpy(name, Unit_name[typeId]);
    args.clear();
    buffs.clear();
    skills.clear();
}
bool PUnit::isHero() const //判断单位是否为英雄
{
    return typeId <= 2;
}
bool PUnit::isWild() const //判断单位是否为野怪
{
    return typeId >= 6;
}
const PArg* PUnit::operator[] (int _typeId) const //按类型编号查询参数
{
    int _sz = args.size();
    for (int i=0; i<_sz; ++i)
        if (_typeId == args[i].typeId || Args_name[_typeId] == args[i].name)
            return &args[i];
    return 0;
}
const PArg* PUnit::operator[] (string _) const //按名称查询参数
{
    int _sz = args.size();
    for (int i=0; i<_sz; ++i)
        if (_ == string(args[i].name))
            return &args[i];
    return 0;
}
const PBuff* PUnit::findBuff(int _typeId) const //按类型编号查询状态
{
    int _sz = buffs.size();
    for (int i=0; i<_sz; ++i)
        if (_typeId == buffs[i].typeId || Buff_name[_typeId] == buffs[i].name)
            return &buffs[i];
    return 0;
}
const PBuff* PUnit::findBuff(string _) const //按名称查询状态
{
    int _sz = buffs.size();
    for (int i=0; i<_sz; ++i)
        if (_ == string(buffs[i].name))
            return &buffs[i];
    return 0;
}
const PSkill* PUnit::findSkill(int _typeId) const //按类型编号查询技能
{
    int _sz = skills.size();
    for (int i=0; i<_sz; ++i)
        if (_typeId == skills[i].typeId || Skill_name[_typeId] == skills[i].name)
            return &skills[i];
    return 0;
}
const PSkill* PUnit::findSkill(string _) const //按名称查询技能
{
    int _sz = skills.size();
    for (int i=0; i<_sz; ++i)
        if (_ == string(skills[i].name))
            return &skills[i];
    return 0;
}
bool PUnit::canMove() const //判断单位目前是否可以移动
{
    if (typeId >= 3 && typeId <= 5) return 0;
    int _sz = buffs.size();
    for (int i=0; i<_sz; ++i)
        switch (buffs[i].typeId)
            case 4: case 7: return 0;
    return 1;
}
bool PUnit::canUseSkill(int _typeId) const //判断单位目前是否可以使用某种技能，_typeId为技能类型编号
{
    const PSkill* _ = findSkill(_typeId);
    if (!_)
        return 0;
    int mp, skill_point;
    const PArg* _arg = (*this)[1]; 
    if (_arg) 
        mp = _arg->val[0]; 
    else 
        mp = 0;
    
    _arg = (*this)[6]; 
    if (_arg)
        skill_point = _arg->val[3];
    else
        skill_point = 0;
    
    bool with_dizzy = findBuff(4), with_reviving = findBuff(7);
    if (with_reviving)
        return 0;

    if (!_typeId)
        return !with_dizzy && !_->cd;
    else if (_typeId >= 20)
        return 1;
    else if (_->maxCd)
        return !with_dizzy && _->level >= 0 && mp >= _->mp && !_->cd;
    else if (_typeId == 19)
        return skill_point;
    else {
        _ = findSkill(_typeId - 1);
        return skill_point && _->level < _->maxLevel;
    }
    return 0;
}

const PUnit* PPlayerInfo::findUnitById(int _id) const //返回编号为_id的单位
{
    int _sz = units.size();
    for (int i=0; i<_sz; ++i)
        if (units[i].id == _id)
            return &units[i];
    return 0;
}
const PUnit* PPlayerInfo::findUnitByPos(Pos _pos) const //返回位置为_pos的单位
{
    int _sz = units.size();
    for (int i=0; i<_sz; ++i)
        if (units[i].pos == _pos)
            return &units[i];
    return 0;
}
void PPlayerInfo::findUnitByTypeId(int _typeId, std::vector<const PUnit*> &_unitList) const//返回所有类型编号为_typeId的单位列表_unitList
{
    int _sz = units.size(); _unitList.clear();
    for (int i=0; i<_sz; ++i)
        if (units[i].typeId == _typeId) 
            _unitList.push_back(&units[i]);
}
void PPlayerInfo::findUnitByName(string _name, std::vector<const PUnit*> &_unitList) const//返回所有名称为_name的单位列表_unitList
{
    int _sz = units.size(); _unitList.clear();
    for (int i=0; i<_sz; ++i)
        if (units[i].name == _name)
            _unitList.push_back(&units[i]);
}
void PPlayerInfo::findUnitByPlayer(int _player, std::vector<const PUnit*> &_unitList) const//返回所有属于玩家_player的单位列表_unitList
{
    int _sz = units.size(); _unitList.clear();
    for (int i=0; i<_sz; ++i)
        if (units[i].player == _player)
            _unitList.push_back(&units[i]);
}
void PPlayerInfo::findUnitInArea(Pos _, int _range, std::vector<const PUnit*> &_unitList) const//返回到点_的距离不超过_range的单位列表_unitList
{
    int _sz = units.size(); _unitList.clear();
    for (int i=0; i<_sz; ++i)
        if (dis2(units[i].pos, _) <= _range)
            _unitList.push_back(&units[i]);
}

const PFlight* PPlayerInfo::findFlightById(int _id) const //返回编号为_id的飞行道具
{
    int _sz = flights.size();
    for (int i=0; i<_sz; ++i)
        if (flights[i].id == _id)
            return &flights[i];
    return 0;
}
void PPlayerInfo::findFlightByTypeId(int _typeId, std::vector<const PFlight*> &_flightList) const//返回所有类型编号为_typeId的飞行道具列表_flightList
{
    int _sz = flights.size(); _flightList.clear();
    for (int i=0; i<_sz; ++i)
        if (flights[i].typeId == _typeId)
            _flightList.push_back(&flights[i]);
}
void PPlayerInfo::findFlightByName(string _name, std::vector<const PFlight*> &_flightList) const//返回所有名称为_name的飞行道具列表_flightList
{
    int _sz = flights.size(); _flightList.clear();
    for (int i=0; i<_sz; ++i)
        if (flights[i].name == _name)
            _flightList.push_back(&flights[i]);
}
void PPlayerInfo::findFlightByPlayer(int _player, std::vector<const PFlight*> &_flightList) const//返回所有属于玩家_player的飞行道具列表_flightList
{
    int _sz = flights.size(); _flightList.clear();
    for (int i=0; i<_sz; ++i)
        if (findUnitById(flights[i].unitId)->player == _player)
            _flightList.push_back(&flights[i]);
}
const PArea* PPlayerInfo::findAreaById(int _id) const //返回编号为_id的作用范围
{
    int _sz = areas.size();
    for (int i=0; i<_sz; ++i)
        if (areas[i].id == _id)
            return &areas[i];
    return 0;
}
void PPlayerInfo::findAreaByCenterPos(Pos _center, std::vector<const PArea*> &_areaList) const//返回所有圆心坐标为_center的作用范围列表_areaList
{
    int _sz = areas.size(); _areaList.clear();
    for (int i=0; i<_sz; ++i)
        if (areas[i].center == _center)
            _areaList.push_back(&areas[i]);
}
void PPlayerInfo::findAreaByTypeId(int _typeId, std::vector<const PArea*> &_areaList) const//返回所有类型编号为_typeId的作用范围列表_areaList
{
    int _sz = areas.size(); _areaList.clear();
    for (int i=0; i<_sz; ++i)
        if (areas[i].typeId == _typeId)
            _areaList.push_back(&areas[i]);
}
void PPlayerInfo::findAreaByName(string _name, std::vector<const PArea*> &_areaList) const//返回所有名称为_name的作用范围列表_areaList
{
    int _sz = areas.size(); _areaList.clear();
    for (int i=0; i<_sz; ++i)
        if (areas[i].name == _name)
            _areaList.push_back(&areas[i]);
}
void PPlayerInfo::findAreaByCamp(int _camp, std::vector<const PArea*> &_areaList) const//返回所有属于阵营_camp的作用范围列表_areaList
{
    int _sz = areas.size(); _areaList.clear();
    for (int i=0; i<_sz; ++i)
        if (areas[i].camp == _camp)
            _areaList.push_back(&areas[i]);
}

Operation::Operation(const Operation &_): id(_.id)//给出typeId和type的其中之一即可，默认为typeId
{
    if (_.typeId >= 0 && _.typeId < Operation_name_size) {
        typeId = _.typeId;
        type = Operation_name[typeId];
    } else {
        typeId = -1;
        for (int i=Operation_name_size-1; i>=0; --i)
            if (_.type == Operation_name[i]) {
                typeId = i;
                break;
            }
        if (typeId >= 0) type = _.type; else type = "Stop";
    }
    targets.clear();
    int _sz = _.targets.size();
    for (int i=0; i<_sz; ++i)
        targets.push_back(_.targets[i]);
}

bool checkPos(Pos A)
{
    return 0 <= A.x && A.x < Map_size && 0 <= A.y && A.y < Map_size;
}

void findShortestPath(const PMap &map, Pos start, Pos dest, std::vector<Pos> &_path)
//寻路，返回从位置start到dest的一条最短路径，考虑悬崖，不考虑其它单位，若路径不存在返回一个负数坐标
{
    _path.clear();
    Pos _0, _1;
    
    int dir_ord[4];
    Q[0] = start;
    ++countF;
    vst[start.x][start.y] = countF;
    for (int front=0, rear=0; front<=rear; ++front) {
        _0 = Q[front];
        for (int i=0; i<4; ++i) dir_ord[i] = i;
        random_shuffle(dir_ord, dir_ord+4);

        for (int i=0; i<4; ++i) {
            _1 = _0 + Pos(dir[dir_ord[i]][0], dir[dir_ord[i]][1]);
            if (checkPos(_1) && abs(map.height[_0.x][_0.y] - map.height[_1.x][_1.y]) <= 1 && vst[_1.x][_1.y] != countF) {
                vst[_1.x][_1.y] = countF;
                Q[++rear] = _1;
                Q_prior[_1.x][_1.y] = _0;
            }
        }
    }

    if (vst[dest.x][dest.y] == countF) {
        for (_0 = dest; _0 != start; _0 = Q_prior[_0.x][_0.y])
            _path.push_back(_0);
        _path.push_back(_0);
        reverse(_path.begin(), _path.end());
    } else _path.push_back(Pos());
}
void findShortestPath(const PMap &map, Pos start, Pos dest, const std::vector<Pos> &blocks, std::vector<Pos> &_path)
//带卡位的寻路，返回从位置start到dest的一条最短路径，blocks中的位置不可经过，考虑悬崖，若路径不存在返回一个负数坐标
{
    int _sz = blocks.size();

    ++countF;
    _path.clear();
    for (int i=0; i<_sz; ++i)
    {
        if (checkPos(blocks[i]))
            vst[blocks[i].x][blocks[i].y] = countF;
    }
    if (!checkPos(start) || !checkPos(dest))
    {
        _path.push_back(Pos());
        return;
    }
    vst[start.x][start.y] = vst[dest.x][dest.y] = countF - 1;
    
    Pos _0, _1;

    int dir_ord[4];
    Q[0] = start;
    vst[start.x][start.y] = countF;
    for (int front=0, rear=0; front<=rear; ++front) {
        _0 = Q[front];
        for (int i=0; i<4; ++i) dir_ord[i] = i;
        random_shuffle(dir_ord, dir_ord+4);

        for (int i=0; i<4; ++i) {
            _1 = _0 + Pos(dir[dir_ord[i]][0], dir[dir_ord[i]][1]);
            if (checkPos(_1) && abs(map.height[_0.x][_0.y] - map.height[_1.x][_1.y]) <= 1 && vst[_1.x][_1.y] != countF) {
                vst[_1.x][_1.y] = countF;
                Q[++rear] = _1;
                Q_prior[_1.x][_1.y] = _0;
            }
        }
    }

    if (vst[dest.x][dest.y] == countF) {
        for (_0 = dest; _0 != start; _0 = Q_prior[_0.x][_0.y])
            _path.push_back(_0);
        _path.push_back(_0);
        reverse(_path.begin(), _path.end());
    } else _path.push_back(Pos());
}

void findShortestPathWithSymbols(const PMap &map, const std::vector<Pos> &symbols, std::vector<Pos> &_path)
//带标志点寻路，返回经过symbols内所有位置的一条最短路径（symbols的首尾元素表示起、终点），考虑悬崖，不考虑其它单位，若路径不存在返回一个负数坐标
{
    _path.clear(); _path.push_back(symbols[0]);
    int _sz = symbols.size(), _sz0;
    std::vector<Pos> segPath;
    for (int i=1; i<_sz; ++i) {
        findShortestPath(map, symbols[i - 1], symbols[i], segPath);
        if (segPath[0].x >= 0) {
            _sz0 = segPath.size();
            for (int j=1; j<_sz0; ++j)
                _path.push_back(segPath[j]);
        } else {
            _path.clear();
            _path.push_back(Pos());
            return;
        }
    }
}
void findShortestPathWithSymbols(const PMap &map, const std::vector<Pos> &symbols, const std::vector<Pos> &blocks, std::vector<Pos> &_path)
//带卡位和标志点的寻路，返回经过symbols内所有位置的一条最短路径（symbols的首尾元素表示起、终点），blocks中的位置不可经过，考虑悬崖，若路径不存在返回一个负数坐标
{
    _path.clear(); _path.push_back(symbols[0]);
    int _sz = symbols.size(), _sz0;
    std::vector<Pos> segPath;
    for (int i=1; i<_sz; ++i) {
        findShortestPath(map, symbols[i - 1], symbols[i], blocks, segPath);
        if (segPath[0].x >= 0) {
            _sz0 = segPath.size();
            for (int j=1; j<_sz0; ++j)
                _path.push_back(segPath[j]);
        } else {
            _path.clear();
            _path.push_back(Pos());
            return;
        }
    }
}

void infectedBySkill(const PPlayerInfo &info, int _unitId, int _typeId, std::vector<const PUnit*> &_unitList)
//返回编号为_unitId的单位目前使用某种技能可能影响到（即在射程内）的单位列表_unitList，_typeId为技能类型编号
{
    _unitList.clear();
    int _sz = info.units.size(), _camp = info.camp; const PUnit* hero = 0;
    for (int i=0; i<_sz; ++i)
        if (info.units[i].id == _unitId) {
            hero = &info.units[i];
            break;
        }
    if (!hero) return;

    _sz = hero->skills.size(); 
    bool skill_ex = 0;
    for (int i=0; i<_sz; ++i)
        if (hero->skills[i].typeId == _typeId) {
            skill_ex = 1;
            break;
        }
    if (!skill_ex) return;

    int _range = 0;
    switch (_typeId) {
        case 0: {
            _sz = hero->args.size();
            for (int i=0; i<_sz; ++i)
                if (hero->args[i].typeId == 5) {
                    _range = hero->args[i].val[0];
                    break;
                }
            break;
        }
        case 1: {
            _range = Charge_range;
            break;
        }
        case 3: {
            _range = Spin_range;
            break;
        }
        case 5: {
            _range = Yell_range;
            break;
        }
        case 7: {
            _range = PiercingArrow_range;
            break;
        }
        case 9: {
            _range = RainyPlace_range;
            break;
        }
        case 15: {
            _range = FlyingBlade_range;
            break;
        }
        case 17: {
            _range = Blink_range;
            break;
        }
    }
    if (!_range) return;

    _sz = info.units.size();
    Pos pos = hero->pos;
    const PUnit* _;
    for (int i=0; i<_sz; ++i)
        if (dis2(pos, info.units[i].pos) <= _range && info.units[i].id != _unitId) {
            _ = &info.units[i];
            if (_typeId < 17 && _->camp == _camp) continue;
            if (_typeId == 1 && _->typeId >= 3 && _->typeId <= 5) continue;
            _unitList.push_back(&info.units[i]);
        }
}


#ifdef player_ai
#undef player_ai
void * _functable[][5];
void initWarpper(size_t *sizes, void * functable[][5]){
    for (int i = 0; i < 9; i++)
        if (_::ss[i] != sizes[i])
            exit(1);

    _functable = functable;
}
#include "dummystd.h"
namespace fake {
    #define std fake
    #include "tinydefines.h"
    #undef std
};

namespace _{
    template<class T>
    struct vector_proxy {
        typedef size_t (*pSize)(void *);
        typedef void (*pPush)(void *, int &v);
        typedef T (*pAt)(void *, int p);

        static size_t size(void *__){
            return ((pSize)functable[ToId<std::vector<T> >::invoke][0])(__);
        }
        static void push(void *__, int &v){
            ((pPush)functable[ToId<std::vector<T> >::invoke][1])(__, v);
        }
        static T at(void *__, int p){
            ((pAt)functable[ToId<std::vector<T> >::invoke][2])(__, p);
        }
    };

    struct string_proxy {
        typedef const char * (*pStr)(void *);
        static const char * c_str(void * __){
            return ((pStr)functable[ToId<std::string>::invoke][0])(__);
        };
    }; 

    template<class Ret, class Org>
    struct ToReal { };

    template<>
    struct ToReal<int,int> { 
        static int invoke(int _) { return _; }
    };

    template<class TRet, class TOrg>
    struct VecToReal<std::vector<TOrg>, fake::vector<TRet> > {
        static std::vector<TOrg> invoke(fake::vector<TRet> *_){
            size_t len = vector_proxy<TRet>::size(_);
            std::vector<TRet> R;
            for (int i = 0; i < len; i++)
                R.push_back(ToReal<TRet, TOrg>::invoke(vector_proxy<TRet>::at(_, i)));
            return R;
        }
    };

    template<>
    struct ToReal<std::string, fake::string> {
        static std::string invoke(fake::string *_){
            return std::string(string_proxy::c_str(_));
        }
    };

    template<>
    struct ToReal<::PMap, fake::PMap> {
        static ::PMap * invoke(fake::PMap *_){
            ::PMap * m = new ::PMap();
            m->playerIds = VecToReal<int, int>::invoke((void*)_->playerIds.buf);
            for (int i = 0; i < Map_size; i++)
                for (int j = 0; j < Map_size; j++)
                    m->height[i][j] = _->height[i][j];
            return m;
        }
    };
    #define copy(name) R.name = _->name;
    #define vcopy(type, name) R.name = VecToReal<::type, fake::type>::invoke(_->name);;
    #define S(type) template<> \
    struct ToReal<::type, fake::type>
    
    #define setpos(pos) R.pos.x = _->pos.x; R.pos.y = _->pos.y;
    S(PArg){
        static ::PArg invoke(fake::PArg *_){
            ::PArg R;
            copy(typeId);
            for (int i = 0; i < 100; i++)
                R.name[i] = _->name[i];
            vcopy(int, val);
        }
    }

    S(PBuff){
        static ::PBuff invoke(fake::PBuff *_){
            ::PBuff R;
            copy(typeId);
            copy(level);
            copy(timeLeft);
            for (int i = 0; i < 100; i++)
                R.name[i] = _->name[i];
        }
    }

    P(PSkill) {
        static ::PSkill invoke(fake::PSkill *_){
            ::PSkill R;
            copy(typeId);
            copy(level);
            copy(maxLevel);
            copy(mp);
            copy(cd);
            copy(maxCd);

            for (int i = 0; i < 100; i++)
                R.name[i] = _->name[i];
        }
    }

    S(PUnit){
        static ::PUnit invoke(fake::PUnit *_){
            ::PUnit R;
            copy(hp);
            copy(mp);
            copy(atk);
            copy(def);
            copy(speed);
            copy(exp);
            copy(range);
            copy(view);
            copy(level);
            copy(typeId);
            copy(id);
            copy(player);
            copy(camp);
            setpos(pos);
            for (int i = 0; i < 100; i++)
                R.name[i] = _->name[i];
            vcopy(PArg, args);
            vcopy(PBuff, buffs);
            vcopy(PSkill, skills);
            return R;
        }
    }

    S(PFlight) {
        static ::PFlight invoke(fake::PFlight *_){
            ::PFlight R;
            copy(typeId);
            copy(id);
            copy(unitId);
            copy(camp);
            copy(speed);
            setpos(pos);
            setpos(target);
            for (int i = 0; i < 100; i++)
                R.name[i] = _->name[i];
        }
    }

    S(PArea){
        static ::PArea invoke(fake::PArea *_){
            ::PArea R;
            copy(typeId);
            for (int i = 0; i < 100; i++)
                R.name[i] = _->name[i];
            copy(id);
            copy(camp);
            copy(timeLeft);
            copy(radius);
            setpos(center);
        }
    }

    S(PPlayerInfo) {
        static ::PPlayerInfo invoke(fake::PPlayerInfo *_){
            ::PPlayerInfo R;
            copy(round);
            copy(player);
            copy(camp);
            vcopy(PUnit, units);
            vcopy(PFlight, flights);
            vcopy(PArea, areas);
            return R;
        }
    };

    #undef copy
    #undef vcopy
    #undef S
    #undef P
};

void player_ai(fake::PMap *map,fake::PPlayerInfo *info,fake::PCommand *cmd){
    ::PMap *_map = ToReal<::PMap, fake::PMap>::invoke(map);
    ::PCommand pc;
    player_ai_1(*_map, ToReal(info), pc);
    for (int i = 0; i < pc.cmds.size(); i++) {
        vector_proxy<PCommand>::push((void*)cmd->cmds.buf, pc.cmds[i]);
    }
    return ;
}

#define player_ai player_ai_1
#endif 