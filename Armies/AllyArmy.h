//
// Created by ahmed on 10/05/2024.
//

#ifndef DS_ALIENINVASION_ALLYARMY_H
#define DS_ALIENINVASION_ALLYARMY_H
#include "../DataStructures/QueueADT.h"
#include "../DataStructures/Queue.h"
#include "../Units/Unit.h"
#include "../Units/SU.h"
class GameManager;
class AllyArmy {
    int nextID;
//    bool WasCalled=false; // a bool to tell if the saver unit was calles by the Earth army before or not.
    LinkedQueue<SU*>*SUQueue;
//    bool Withdrawed=false;

public:
    AllyArmy();
    void AddSU(SU* SUnit);
    int getNumOfSaverUnits() const;
    SU* RemoveSU();
    LinkedQueue<SU*>* getSUQueue() const;
    int getNextID() const;

    void PrintAliveSaverUnits() const;

    void incrementNextID();

    void Attack(GameManager* gameptr);
//    bool GetWascalled()const {return WasCalled;}
//    void SetWascalled(bool call){ WasCalled=call;}

    bool GetWithdrawed() const;
    ~AllyArmy();

};


#endif //DS_ALIENINVASION_ALLYARMY_H
