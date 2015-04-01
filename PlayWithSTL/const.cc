#include "sdk.h"
#include "const.h"

const string Area_name[] = {"RainyPlace"};
const string Args_name[] = {"Hp", "Mp", "Atk", "Def", "Speed", "Range", "Exp", "View", "LastHit", "OnlyTarget"};
const string Buff_name[] = {"Hided", "Rainy", "Yelled", "Yelling", "Dizzy", "Striking", "Slow", "Reviving"};
const string Flight_name[] = {"FlightBlade", "SignalArrow"};
const string Skill_name[] = {"Attack", "Charge", "ChargeLU", "Spin", "SpinLU", "Yell", "YellLU", "PiercingArrow", "PALU", "ArrowsRain", "ARLU", "PowerUp", "PULU",
	"Hide", "HideLU", "FlyingBlade", "FBLU", "Blink", "BlinkLU", "YellowPoint", "ChooseFighter", "ChooseArcher", "ChooseAssassin"};
const char* Unit_name[] = {"Fighter", "Archer", "Assassin", "Tower", "Spring", "Chooser", "Dog", "Bow", "Wolf", "StoneMan", "Dragon", "Roshan"};
const string Operation_name[] = {"Attack", "Charge", "ChargeLU", "Spin", "SpinLU", "Yell", "YellLU", "PiercingArrow", "PALU", "ArrowsRain", "ARLU", "PowerUp", "PULU",
	"Hide", "HideLU", "FlyingBlade", "FBLU", "Blink", "BlinkLU", "YellowPoint", "ChooseFighter", "ChooseArcher", "ChooseAssassin", "Move", "Stop"};


Pos unitTarget(Pos start, Pos drct, int _speed, int _timeLeft)                           //返回从start发出，移动方向为drct，移动速度为_speed的单位在_timeLeft回合后的位置
{
    return start + _speed * _timeLeft * drct;
}

UnitArgs::UnitArgs(int _typeId, int _hp, int _atk, int _def, int _speed, int _range, int _view, int _maxcd)
	:typeId(_typeId), hp(_hp), atk(_atk), def(_def), speed(_speed), range(_range), view(_view), attack_maxcd(_maxcd)
{
    name = Unit_name[_typeId];
    poslist.clear();
}

void UnitArgs::newPos(Pos _)                                                             //添加位置
{
    poslist.push_back(_);
}

    UnitArgs::UnitArgs(int _typeId, int _hp, int _atk, int _def, int _speed, int _range, int _exp, int _view, int _maxcd, int _time, const Pos* _begin, const Pos* _end):
        typeId(_typeId), hp(_hp), atk(_atk), def(_def), speed(_speed), range(_range), exp(_exp), view(_view), attack_maxcd(_maxcd), reviving_time(_time)
    {
        name = Unit_name[_typeId];
        poslist.clear();
        for (const Pos* i=_begin; i<_end; ++i)
            newPos(*i);
    }

    HeroArgs::HeroArgs(int _typeId, int _hp, int _mp, int _atk, int _def, int _speed, int _range, int _view, int _maxcd,
             int _hp_delta, int _atk_delta, int _def_delta):
        UnitArgs(_typeId, _hp, _atk, _def, _speed, _range, _view, _maxcd), mp(_mp), hp_delta(_hp_delta), atk_delta(_atk_delta), def_delta(_def_delta)
    {
        name = Unit_name[_typeId];
    }

    SpecialUnitArgs::SpecialUnitArgs(int _player, int _typeId, int _hp, int _atk, int _def, int _range, int _view, int _maxcd, const Pos* _begin, const Pos* _end):
        player(_player), UnitArgs(_typeId, _hp, _atk, _def, 0, _range, _view, _maxcd)
    {
        name = Unit_name[_typeId];
        for (const Pos* i=_begin; i<_end; ++i)
            newPos(*i);
    }
