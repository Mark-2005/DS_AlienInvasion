//
// Created by ahmed on 06/03/2024.
//


#include "../DataStructures/QueueADT.h"
#include "../DataStructures/DEqueue.h"
#include "../DataStructures/Queue.h"
#include "../DataStructures/Monsters_arr.h"
#include "../Units/AD.h"
#include "../Units/AM.h"
#include "../Units/AS.h"
class GameManager;
#ifndef DS_ALIENINVASION_ALIENARMY_H
#define DS_ALIENINVASION_ALIENARMY_H


class AlienArmy {
    int nextID;
    Monsters_arr *AMArr;
    LinkedQueue<AS*>*ASQueue;
    DEqueue<AD*>*ADQueue;

public:
    AlienArmy();
    void AddAM(AM* MonsterToAdd);
    void AddAS(AS* SoldierToAdd);
    void AddAD(AD* DroneToAdd);
    void AddUnit(Unit* Unittoadd);

    int getNumOfAlienUnits() const;
    AM* RemoveAM();
    AS* RemoveAS();
    AD* RemoveADFront();
    AD* RemoveADBack();
    Monsters_arr* getMonstersArr() ;
    LinkedQueue<AS*>* getASQueue() const;
    DEqueue<AD*>* getADQueue() const;
    int getNextID() const;
    void PrintAlienAliveUnits() const;
    void incrementNextID();
    void Attack(GameManager* gameptr);
    ~AlienArmy();
};


#endif //DS_ALIENINVASION_ALIENARMY_H
