//
// Created by ahmed on 06/03/2024.
//
#include "Unit.h"
#pragma once
#ifndef DS_ALIENINVASION_AD_H
#define DS_ALIENINVASION_AD_H
class GameManager;
class ET;
class EG;

class AD:public Unit {
    ET* AttackET(GameManager* gameptr, int TS,bool Interactive);
    EG* AttackEG(GameManager* gameptr, int TS,bool Interactive);
public:
    AD(int id,int h,int p, int ad);
    AD(){Type="AlienDrone";}
    AD(int h,int p, int ad);
    void Attack(GameManager*gameptr){}
    void Attack(GameManager* gameptr,int AttackWho);
    static int ADcount;
};

#endif //DS_ALIENINVASION_AD_H