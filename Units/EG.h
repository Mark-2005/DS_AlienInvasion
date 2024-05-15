//
// Created by ahmed on 06/03/2024.
//
#include"Unit.h"

#ifndef DS_ALIENINVASION_EG_H
#define DS_ALIENINVASION_EG_H

class GameManager;
class AM;
class AD;

class EG : public Unit{
private:
    AM* AttackMonster(GameManager* gameptr, int TS,bool Interactive);
    AD* AttackDrone(GameManager*gameptr, int TS, bool Interactive,AD *&ADptr, int num=1);
    //
public:
    EG(){Type="EarthGunnery";}
    EG(int id, int h, int p,int ac);
    EG(int h, int p,int ac);
    int getPri(){return (Health+Power)/2;}
    void Attack(GameManager* gameptr);
    static int EGcount;
};

#endif //DS_ALIENINVASION_EG_H
