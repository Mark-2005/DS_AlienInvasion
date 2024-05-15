//
// Created by ahmed on 06/03/2024.
//
#pragma once
#include "../DataStructures/QueueADT.h"
#include "../DataStructures/PriorityQueue.h"
#include "../DataStructures/Queue.h"
#include "../DataStructures/StackADT.h"
#include "../DataStructures/Stack.h"
#include "../Units/Unit.h"
#include "../Units/ET.h"
#include "../Units/EG.h"
#include "../Units/ES.h"
#include <iostream>
#include "../Units/HU.h"
class GameManager;
using namespace std;

class EarthArmy {

private:
    int nextID;
    Stack<ET*>*ETStack;
    LinkedQueue<ES*>*ESQueue;
    priQueue<EG*>*EGPriQueue;

    Stack<HU*>* HList;
    int Infected_count=0;
public:
    EarthArmy();
    int getInfectedCount() const{return Infected_count;}
    void AddES(ES* ESUnit);
    void AddET(ET* ETUnit);
    void AddEG(EG* EGUnit);
    void AddUnit(Unit* Unittoadd);
    void AddHU(HU* HUnit);

    //bool IsAnyInfected();

    int getNumOfEarthUnits() const;

    ET* RemoveET();
    EG* RemoveEG();
    ES* RemoveES();
    ES* RemoveRandomES();

    HU* RemoveHU();

    void HealAttack(GameManager* gameptr);

    Stack<ET*>* getETStack() const ;
    LinkedQueue<ES*>* getESQueue() const;
    priQueue<EG*>* getEGPriQueue() const;

    Stack<HU*>* getHLStack() const ;

    int getNextID() const;

    void PrintEarthAliveUnits() const;

    void incrementNextID();
    void SpreadInfection(GameManager* gameptr);

    void Attack(GameManager* gameptr);
    ~EarthArmy();


    int getPer_Infected();
    void incrementInfected_count(){Infected_count++;}
    void decrementInfected_count(){Infected_count--;}
    int getNumInfected()
    {
        int count=0;
        LinkedQueue<ES*> temp;
        ES* es;
        while(ESQueue->dequeue(es))
        {
            if(es->getIsInfected()==true)
                count++;
            temp.enqueue(es);
        }
        while(temp.dequeue(es))
            ESQueue->enqueue(es);

        return count;
    }
};


 //DS_ALIENINVASION_EARTHARMY_H
