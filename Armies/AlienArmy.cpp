//
// Created by ahmed on 06/03/2024.
//

#include "AlienArmy.h"
#include "../GameManager/GameManager.h"
AlienArmy::AlienArmy(){
    nextID=2000;
    ADQueue=new DEqueue<AD*>;
    ASQueue=new LinkedQueue<AS*>;
    AMArr=new Monsters_arr;
}


void AlienArmy::AddAD(AD *ADUnit) {ADQueue->enqueue(ADUnit);}
void AlienArmy::AddAM(AM *AMUnit) {AMArr->AddMonster(AMUnit);}
void AlienArmy::AddAS(AS *ASUnit) {ASQueue->enqueue(ASUnit);}

AD* AlienArmy::RemoveADFront() {
    AD* RemoveAD;
    ADQueue->dequeue(RemoveAD);
    return RemoveAD;
}
AD* AlienArmy::RemoveADBack() {
    AD* RemoveAD;
    ADQueue->dequeueBack(RemoveAD);
    return RemoveAD;

}

AM* AlienArmy::RemoveAM() {
    AM* RemovedAM;
    AMArr->RemoveAnyMonster(RemovedAM);
    return RemovedAM;
}

AS* AlienArmy::RemoveAS() {
    AS* ASRemove;
    ASQueue->dequeue(ASRemove);
    return ASRemove;
}

LinkedQueue<AS*>* AlienArmy::getASQueue() const{
    return ASQueue;
}
DEqueue<AD*>* AlienArmy::getADQueue() const{
    return ADQueue;
}
Monsters_arr* AlienArmy::getMonstersArr()
{
    return AMArr;
}
int AlienArmy::getNextID() const{return nextID;}

void AlienArmy::PrintAlienAliveUnits() const{
    cout<<"====================Alien Army Alive Units===================="<<endl;
    cout<<ASQueue->getCount()<<" AS ";
    if (ASQueue->isEmpty()) cout<<"[ ]"<<endl;
    ASQueue->printQueue();
    cout<<endl;

    cout<<ADQueue->getCount()<<" AD ";
    if (ADQueue->isEmpty()) cout<<"[ ]"<<endl;
    ADQueue->printQueue();
    cout<<endl;

    cout<<AMArr->getCount()<<" AM ";
    if (AMArr->isEmpty()) cout<<"[ ]"<<endl;
    AMArr->Printarr();
    cout<<endl;
}

void AlienArmy::AddUnit(Unit* UnitToAdd){

    if(UnitToAdd->getType()=="AlienMonster"){
        AM* AMUnit = dynamic_cast<AM*>(UnitToAdd);
        AMArr->AddMonster(AMUnit);
        return;
    }

    if(UnitToAdd->getType()=="AlienSoldier"){
        AS* ASUnit = dynamic_cast<AS*>(UnitToAdd);
        ASQueue->enqueue(ASUnit);
        return;
    }

    if(UnitToAdd->getType()=="AlienDrone"){
        AD* ADUnit=dynamic_cast<AD*>(UnitToAdd);
        ADQueue->enqueue(ADUnit);
        return;
    }

}

void AlienArmy::incrementNextID() {nextID++;}

void AlienArmy::Attack(GameManager *gameptr)
{
    bool Interactive=gameptr->getInteractive();

    if(ASQueue->getCount()>0)
    {
        AS* as;
        ASQueue->peek(as);

        if (Interactive==true) cout<<"AS "<<*as<<" shots [ ";

        as->Attack(gameptr);
        if (Interactive==true) cout<<" ]"<<endl;
    } else {
        if(Interactive==true) cout<<"No enough AS to attack\n";
    }

    if(AMArr->getCount()>0)
    {
        AM* am;
        am=RemoveAM();
        if (Interactive) cout<<"AM "<<*am<<" shots [ ";
        am->Attack(gameptr);
        if (Interactive) cout<<"]"<<endl;
        AMArr->AddMonster(am);
    } else {
        if(Interactive) cout <<"No enough AM to attack\n";
    }

    if(ADQueue->getCount()<=1){
        if(Interactive) cout<<"No enough AD to attack\n";
    } else {
        AD* ad1;
        AD* ad2;
        ADQueue->peek(ad1);
        ADQueue->peekBack(ad2);

        if (Interactive) cout<<"AD "<<*ad1<<" shots [ ";
        ad1->Attack(gameptr,1);
        if (Interactive) cout<<"]"<<endl;

        if (Interactive) cout<<"AD "<<*ad2<<" shots [ ";
        ad2->Attack(gameptr,2);
        if (Interactive) cout<<"]"<<endl;
    }
}

int AlienArmy::getNumOfAlienUnits() const {
    return ASQueue->getCount()+AMArr->getCount()+ADQueue->getCount();
}

AlienArmy::~AlienArmy(){
    delete AMArr;
    delete ADQueue;
    delete ASQueue;
}