//
// Created by ahmed on 10/05/2024.
//

#ifndef DS_ALIENINVASION_SU_H
#define DS_ALIENINVASION_SU_H
#include "Unit.h"
class GameManager;

class SU: public Unit {

public:
    SU(int,int,int,int);
    ~SU(){}
    void Attack(GameManager* Gameptr);
    static int SUcount;
};


#endif //DS_ALIENINVASION_SU_H
