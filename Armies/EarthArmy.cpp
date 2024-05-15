//
// Created by ahmed on 06/03/2024.
//

#include "EarthArmy.h"
#include "../GameManager/GameManager.h"
#include "cmath"

EarthArmy::EarthArmy(){
    nextID=1;
    ETStack=new Stack<ET*>;
    ESQueue=new LinkedQueue<ES*>;
    EGPriQueue=new priQueue<EG*>;
    HList=new Stack<HU*>;
}

void EarthArmy::AddUnit(Unit* UnitToAdd){

    if(UnitToAdd->getType()=="EarthTank"){
        ET* ETUnit = dynamic_cast<ET*>(UnitToAdd);
        ETStack->push(ETUnit);
        return;
    }

    if(UnitToAdd->getType()=="EarthSoldier"){
        ES* ESUnit = dynamic_cast<ES*>(UnitToAdd);
        ESQueue->enqueue(ESUnit);
        return;
    }

    if(UnitToAdd->getType()=="EarthGunnery"){
        EG* EGUnit=dynamic_cast<EG*>(UnitToAdd);
        EGPriQueue->enqueue(EGUnit,EGUnit->getPri());
        return;
    }

}

void EarthArmy::AddET(ET *ETUnit) {ETStack->push(ETUnit);}
void EarthArmy::AddEG(EG *EGUnit) {EGPriQueue->enqueue(EGUnit,EGUnit->getPri());}
void EarthArmy::AddES(ES *ESUnit) {ESQueue->enqueue(ESUnit);}

void EarthArmy::AddHU(HU* HUnit) {HList->push(HUnit);}


ET* EarthArmy::RemoveET() {
    ET*RemoveET= nullptr;
    ETStack->pop(RemoveET);
    return RemoveET;
}

EG* EarthArmy::RemoveEG() {
    EG* RemoveEG=nullptr; int pri;
    EGPriQueue->dequeue(RemoveEG,pri);
    return RemoveEG;
}

ES* EarthArmy::RemoveES() {
    ES* RemovedES=nullptr;
    ESQueue->dequeue(RemovedES);
    return RemovedES;
}


HU* EarthArmy::RemoveHU() {
    HU*RemoveHU= nullptr;
    HList->pop(RemoveHU);
    return RemoveHU;
}

Stack<ET*>* EarthArmy::getETStack() const {
    return ETStack;
}

LinkedQueue<ES*>* EarthArmy::getESQueue() const {
    return ESQueue;
}

priQueue<EG*>* EarthArmy::getEGPriQueue() const {
    return EGPriQueue;
}

Stack<HU*>* EarthArmy::getHLStack() const {
    return HList;
}

int EarthArmy::getNextID() const {return nextID;}

void EarthArmy::PrintEarthAliveUnits() const{
    cout<<"====================Earth Army Alive Units===================="<<endl;
    cout<<ESQueue->getCount()<<" ES ";
    if (ESQueue->isEmpty()) cout<<"[ ]"<<endl;
    ESQueue->printQueue();
    cout<<endl;

    cout<<ETStack->getCount()<<" ET ";
    if (ETStack->isEmpty()) cout<<"[ ]"<<endl;
    ETStack->printStack();
    cout<<endl;

    cout<<EGPriQueue->GetCount()<<" EG ";
    if (EGPriQueue->isEmpty()) cout<<"[ ]"<<endl;
    EGPriQueue->printPriQueue();
    cout<<endl;

    cout<<HList->getCount()<<" HU";
    if (HList->isEmpty()) cout<<"[ ]"<<endl;
    HList->printStack();
    cout<<endl;

}

void EarthArmy::incrementNextID() {nextID++;}

void EarthArmy::Attack(GameManager *gameptr)
{
    bool Interactive=gameptr->getInteractive();

    if(ESQueue->getCount()>0)
    {
        ES* es;
        es=RemoveES();

        if (Interactive==true) cout<<"ES "<<*es<<" shots [ ";

        es->Attack(gameptr);
        if (Interactive==true) cout<<"]"<<endl;
        AddES(es);
    } else {
        if(Interactive==true) cout<<"No enough ES to attack\n";
    }

    if(ETStack->getCount()>0)
    {
        ET* et;
        et=RemoveET();
        if (Interactive) cout<<"ET "<<*et<<" shots [ ";
        et->Attack(gameptr);
        if (Interactive) cout<<"]"<<endl;
        AddET(et);
    } else {
        if(Interactive) cout <<"No enough ET to attack\n";
    }

    if(EGPriQueue->GetCount()>0)
    {
        EG* eg;
        int pri;

        pri=(eg->getHealth()+eg->getPower())/2;
        EGPriQueue->dequeue(eg,pri);
        if (Interactive) cout<<"EG "<<*eg<<" shots [ ";
        eg->Attack(gameptr);
        if (Interactive) cout<<"]"<<endl;
        EGPriQueue->enqueue(eg,pri);
    } else {
        if(Interactive) cout <<"No enough EG to attack\n";
    }

}

void EarthArmy::HealAttack(GameManager* gameptr)
{
    bool Interactive=gameptr->getInteractive();

    if(HList->getCount()>0)
    {
        HU* hu;
        HList->pop(hu);
        hu->Attack(gameptr);
    }
    else
    {
        if (Interactive)
            cout<<"no enough HU to heal"<<endl;
    }
}

int EarthArmy::getNumOfEarthUnits() const{
    return ETStack->getCount()+ESQueue->getCount()+EGPriQueue->GetCount();
}

int EarthArmy::getPer_Infected()
{
    int Per;
    int NumofEUnits=getESQueue()->getCount();
    if(NumofEUnits==0)
        Per=0;
    else {
        int infected = getNumInfected();
        Per = static_cast<int>(ceil((static_cast<float>(infected) / static_cast<float>(NumofEUnits)) * 100.0));
    }
    return Per;
}

ES* EarthArmy::RemoveRandomES(){
    if(ESQueue->getCount()==0) return nullptr;
    else{
        ES*es; ES* esToReturn;
        LinkedQueue<ES*>* ESTempList=new LinkedQueue<ES*>;
        int n = rand() % ESQueue->getCount();
        for(int i=1;i<n;i++){
            ESQueue->dequeue(es);
            ESTempList->enqueue(es);
        }
        ESQueue->dequeue(es);
        while(ESTempList->dequeue(esToReturn)){
            ESQueue->enqueue(esToReturn);
        }
        delete ESTempList;
        return es;
    }
}

void EarthArmy::SpreadInfection(GameManager* gameptr)
{

    if(getNumInfected()>0&&getNumInfected()!=ESQueue->getCount()) {
        int Prob = gameptr->RandomAB();
        if (Prob <= 2) {
            ES *infES = RemoveRandomES();

            if (infES->getIsInfected() || infES->getIsImmune()) {
                if (gameptr->getInteractive())
                    cout << "The random soldier is already infected or immune, so can't spread disease "<<*infES<<endl;
            }
            else {
                infES->setIsInfected(true);
                gameptr->IncrementTotalInfectedES();
                if (gameptr->getInteractive()) cout << *infES << " was infected due to the spread" << endl;
            }
            AddES(infES);
        }
    }
}

EarthArmy::~EarthArmy(){
    delete ETStack;
    delete ESQueue;
    delete EGPriQueue;
    delete HList;
}
