//
// Created by ahmed on 04/04/2024.
//
#include "Unit.h"
#ifndef DS_ALIENINVASION_AS_H
#define DS_ALIENINVASION_AS_H

class GameManager;
class SU;
class AS:public Unit {
private:
    ES* AttackES(GameManager* gameptr,bool Interactive);
    SU* AttackSU(GameManager* gameptr,bool Interactive);
public:
    AS(){Type="AlienSoldier";}
    AS(int,int,int,int);
    AS(int,int,int);
    ~AS();
    void Attack(GameManager* gameptr);
    static int AScount;
};


#endif //DS_ALIENINVASION_AS_H
