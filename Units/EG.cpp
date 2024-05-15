//
// Created by ahmed on 06/03/2024.
//
#include "../GameManager/GameManager.h"
#include "EG.h"
#include "AM.h"
#include "AD.h"
#include"cmath"

int EG::EGcount=0;
EG::EG(int id, int h, int p,int ac) {
    setID(id);
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    Type="EarthGunnery";
    EGcount++;
}

EG::EG(int h, int p,int ac) {

    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    Type="EarthGunnery";
}

AM* EG::AttackMonster(GameManager *gameptr, int TS, bool Interactive) {
    AM* AMToAttack= gameptr->getAlienArmy()->RemoveAM();
    UAP=(Power*Health/100.0)/sqrt(AMToAttack->getHealth());
    AMToAttack->setHealth(AMToAttack->getHealth()-UAP);
    if (AMToAttack->getHealth()<0) AMToAttack->setHealth(0);

    bool done=false;

    if(AMToAttack->getTA()==0) {
        AMToAttack->setTA(TS);
        AMToAttack->setDF(TS-AMToAttack->getTJ());
    }

    if(AMToAttack->getHealth()==0)
    {
        gameptr->MoveToKilledList(AMToAttack);
        done=true;
    }

    if(Interactive) cout<<*AMToAttack<<" ";
   if(!done) return AMToAttack;
   else return nullptr;
}

AD* EG::AttackDrone(GameManager *gameptr, int TS, bool Interactive, AD*& ADptr, int num) {

    bool done=false;
    AD* ADToAttack;
    ADToAttack=gameptr->getAlienArmy()->RemoveADFront();

    UAP=(Power*Health/100.0)/sqrt(ADToAttack->getHealth());
    ADToAttack->setHealth(ADToAttack->getHealth()-UAP);
    if (ADToAttack->getHealth()<0) ADToAttack->setHealth(0);

    if(ADToAttack->getTA()==0) {
        ADToAttack->setTA(TS);
        ADToAttack->setDF(TS-ADToAttack->getTJ());
    }

    if (Interactive) cout<<*ADToAttack<<" ";

    if (num==2){
        ADptr=gameptr->getAlienArmy()->RemoveADBack();
        UAP=(Power*Health/100.0)/sqrt(ADptr->getHealth());
        ADptr->setHealth(ADptr->getHealth()-UAP);
        if(ADptr->getHealth()<0) ADptr->setHealth(0);
        if(ADptr->getTA()==0) {
            ADptr->setTA(TS);
            int TJ=ADptr->getTJ();
            ADptr->setDF(TS -TJ);
        }
        if (Interactive) cout<<*ADptr<<" ";
    }
     return ADToAttack;
}

void EG::Attack(GameManager *gameptr) {
    int TS = gameptr->getCurrentTimeStep();
    LinkedQueue<AM *> *AMTempList = new LinkedQueue<AM *>;
    LinkedQueue<AD *> *ADTempList = new LinkedQueue<AD *>;
    bool Interactive = gameptr->getInteractive();

    for (int i = 0; i < AttackCapacity; i++) {
        if(i<ceil(AttackCapacity/2.0)) {
            if (gameptr->getAlienArmy()->getMonstersArr()->getCount() == 0) {
                if (gameptr->getAlienArmy()->getADQueue()->getCount() == 0) {
                    break;

                } else if (gameptr->getAlienArmy()->getADQueue()->getCount() == 1) {
                    AD *AttackedAD = AttackDrone(gameptr, TS, Interactive,AttackedAD);
                    if (AttackedAD->getHealth()>0) ADTempList->enqueue(AttackedAD);
                    else gameptr->MoveToKilledList(AttackedAD);

                } else {
                    AD *AttackedAD2;
                    AD *AttackedAD1 = AttackDrone(gameptr, TS, Interactive,AttackedAD2,2);
                    if (AttackedAD1->getHealth()>0) ADTempList->enqueue(AttackedAD1);
                    else gameptr->MoveToKilledList(AttackedAD1);
                    if (AttackedAD2->getHealth()>0) ADTempList->enqueue(AttackedAD2);
                        else gameptr->MoveToKilledList(AttackedAD2);
                }
            } else {
                AM *AttackedAM = AttackMonster(gameptr, TS, Interactive);
                if (AttackedAM!=nullptr) AMTempList->enqueue(AttackedAM);
            }
        } else {
                if (gameptr->getAlienArmy()->getADQueue()->getCount() == 0) {
                    if(gameptr->getAlienArmy()->getMonstersArr()->getCount()==0)
                        break;
                    else {
                        AM *AttackedAM = AttackMonster(gameptr, TS, Interactive);
                        if (AttackedAM!= nullptr) AMTempList->enqueue(AttackedAM);
                    }
                } else {
                    if (gameptr->getAlienArmy()->getADQueue()->getCount() == 1) {
                        AD *AttackedAD = AttackDrone(gameptr, TS, Interactive,AttackedAD);
                        if (AttackedAD->getHealth()==0) gameptr->MoveToKilledList(AttackedAD);
                        else ADTempList->enqueue(AttackedAD);

                    } else {
                        AD *AttackedAD2;
                        AD *AttackedAD1 = AttackDrone(gameptr, TS, Interactive,AttackedAD2,2);
                        if (AttackedAD1->getHealth()==0) gameptr->MoveToKilledList(AttackedAD1);
                        else ADTempList->enqueue(AttackedAD1);
                        if (AttackedAD2->getHealth()==0) gameptr->MoveToKilledList(AttackedAD2);
                        else ADTempList->enqueue(AttackedAD2);
                    }
                }
        }
    }
    AD* ptr; AM*AMptr;
    while (ADTempList->dequeue(ptr)){
        gameptr->getAlienArmy()->AddAD(ptr);
    }

    while (AMTempList->dequeue(AMptr)){
        gameptr->getAlienArmy()->AddAM(AMptr);
    }

    delete ADTempList;
    delete AMTempList;
}