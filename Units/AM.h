//
// Created by ahmed on 06/03/2024.
//
#pragma once
#ifndef DS_ALIENINVASION_AM_H
#define DS_ALIENINVASION_AM_H
#include "Unit.h"
class GameManager;
class ET;
class ES;
class SU;
class AM: public Unit {
    ET* AttackET(GameManager* gameptr,bool Interactive);
    ES* AttackES(GameManager* gameptr,bool Interactive);
    SU* AttackSU(GameManager* gameptr,bool Interactive);
    bool Virus;
public:
    bool isVirus() const;

public:
    AM(int id,int h,int p,int ac,bool v);
    AM(int h,int p,int ac);
    AM(){Type="AlienMonster";}
    void Attack(GameManager* gameptr);
    static int AMcount;
};
static ostream& operator<<(ostream& Output, const AM& am)
{
    if(am.isVirus())
        Output<<"#";
    Output<<am.getID()<<" ";
    return Output;
};

#endif //DS_ALIENINVASION_AM_H

