//
// Created by ahmed on 04/04/2024.
//
#include "Unit.h"

#ifndef DS_ALIENINVASION_ES_H
#define DS_ALIENINVASION_ES_H

class GameManager;
class ES:public Unit {
private:
//    bool Infected=false;
    int TH; //the timestep where the soldier joined the UML
    const int initialHealth;
    bool IsInfected=false;
    bool IsImmune=false;
public:
    //ES(){Type="EarthSoldier";}
    ES(int,int,int,int);
    //ES(int,int,int);
    ~ES(){}
//    void setInfected(bool infected){Infected=infected;}
//    bool IsInfected(){return Infected;}
    int GetTH() const;
    int getInitialHealth() const;
    void SetTH(int th);
    void Attack(GameManager* gameptr);

    bool getIsInfected() const;

    void setIsInfected(bool isInfected);

    bool getIsImmune() const;

    void setIsImmune(bool isImmune);

    void SpreadInfection(ES* es);
    static int EScount;
};

static ostream& operator<<(ostream& Output, const ES& es)
{
    if(es.getIsInfected())
        Output<<"$";
    Output<<es.getID()<<" ";
    return Output;
};
#endif //DS_ALIENINVASION_ES_H
