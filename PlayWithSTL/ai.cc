#include "sdk.h"

bool in_attack_range(const PUnit &t, const Pos& tar)
{
    return dis2(t.pos, tar) <= t.range;
}

void player_ai(const PMap &map, const PPlayerInfo &info, PCommand &cmd)
{
    int player = info.player;
    cmd.cmds.clear();
    if (info.round == 0)
    {
        for (int i = 0; i < info.units.size(); i ++)
        {
            if (info.units[i].player == player)
            {
                Operation op;
                op.id = info.units[i].id;
                if (op.id % 3 == 0)
                    op.type = "ChooseArcher";
                if (op.id % 3 == 1)
                    op.type = "ChooseFighter";
                if (op.id % 3 == 2)
                    op.type = "ChooseAssassin";
                op.targets.clear();
                cmd.cmds.push_back(op);
            }
        }
    }
    else
    {
        for (int i = 0; i < info.units.size(); i ++)
        {
            if (info.units[i].player == player)
            {
                const PUnit &t = info.units[i];
                bool fighting = false;
                Operation op;
                op.id = t.id;

                if (t.skills[0].cd == 0)//attack
                {
                    for (int j = 0; j < info.units.size(); j ++)
                        if (info.units[j].player != player && !info.units[j].findSkill("Reviving")
                                && info.units[j].hp > 0)//enemy
                        {
                            if (in_attack_range(t, info.units[j].pos))
                            {
                                op.type = "Attack";
                                op.targets.push_back(info.units[j].pos);
                                fighting = true;
                                break;
                            }
                        }
                }
                
                if (!fighting)
                {
                    Pos tower = info.player ? Player0_tower_pos[1] : Player1_tower_pos[1];
                    if (!in_attack_range(t, tower))
                    {
                        op.type = "Move";
                        findShortestPath(map, t.pos, tower, op.targets);
                    }
                }
                cmd.cmds.push_back(op);
            }
        }
    }
}
