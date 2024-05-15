//
// Created by ahmed on 10/05/2024.
//

#include "AllyArmy.h"
#include"../GameManager/GameManager.h"
#include"cmath"
AllyArmy::AllyArmy(){
    nextID=4000;
    SUQueue=new LinkedQueue<SU*>;
}

void AllyArmy::AddSU(SU *SaverUnit) {SUQueue->enqueue(SaverUnit);}

SU* AllyArmy::RemoveSU() {
    SU* RemovedSU=nullptr;
    SUQueue->dequeue(RemovedSU);
    return RemovedSU;
}

LinkedQueue<SU*>* AllyArmy::getSUQueue() const {
    return SUQueue;
}

int AllyArmy::getNextID() const {return nextID;}

void AllyArmy::incrementNextID() {nextID++;}

void AllyArmy::PrintAliveSaverUnits() const {
    cout << "====================Saver Army Alive Units====================" << endl;
    cout << SUQueue->getCount() << " SU ";
    if (SUQueue->isEmpty()) cout << "[ ]" << endl;
    SUQueue->printQueue();
    cout << endl;
}

int AllyArmy::getNumOfSaverUnits() const{
    return SUQueue->getCount();
}

AllyArmy::~AllyArmy(){
    delete SUQueue;
}

void AllyArmy::Attack(GameManager *gameptr) {
    bool Interactive = gameptr->getInteractive();
//    int Per = gameptr->getEarthArmy()->getPer_Infected();


//    if (Per == 0 &&
//        WasCalled) // to withdraw the SU army if al the Soldiers are healed  WasCalled to know if there was ES infected before
//    {
//        Withdrawed = true;


    if (SUQueue->getCount() != 0) {
        SU *tempSU = RemoveSU();
        if (Interactive) cout << "SU" << *tempSU << "shots[ ";
        tempSU->Attack(gameptr);
        if (Interactive) cout << " ]" << endl;
    } else {
        if (Interactive == true) cout << "No enough SU to attack\n";
    }


}

//bool AllyArmy::GetWithdrawed() const
//{
//    return Withdrawed;
//}