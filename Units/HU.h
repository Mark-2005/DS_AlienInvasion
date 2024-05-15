//
// Created by DELL on 16/04/2024.
//

#ifndef DS_ALIENINVASION_HU_H
#define DS_ALIENINVASION_HU_H
#include "Unit.h"
//#include "../GameManager/GameManager.h"
class GameManager;

class HU : public Unit{
    //static int HUCount;
public:
    HU(){Type="HealUnit";}
    HU(int,int,int,int);
    HU(int,int,int);
    ~HU(){}

    void Attack(GameManager* pGame);
    static int HUcount;

};


#endif //DS_ALIENINVASION_HU_H
