//
// Created by ahmed on 06/03/2024.
//

#ifndef DS_ALIENINVASION_ET_H
#define DS_ALIENINVASION_ET_H

#include "Unit.h"

#include "../DataStructures/Stack.h"
#include "../DataStructures/Node.h"
#include<iostream>
class GameManager;
class AS;
class AM;
class ET: public Unit{
private:
    int TH; //the timestep where the tank joined the UML
    const int initialHealth;
    AS* AttackAs(GameManager* gameptr,bool Interactive);
    AM* AttackAm(GameManager* gameptr,bool Interactive);
public:
    //ET(){Type="EarthTank";}
    ET(int,int,int,int);
    //ET(int,int,int);
    ~ET(){}
    void SetTH(int th);
    int GetTH() const;
    int getInitialHealth() const;
    void Attack(GameManager*gameptr);

    static int ETcount;
};

#endif //DS_ALIENINVASION_ET_H