//
// Created by ahmed on 04/04/2024.
//
#include "../GameManager/GameManager.h"
#include "AS.h"
#include "cmath"
int AS::AScount=0;
AS::AS(int id, int h, int p,int ac) {
    Type="AlienSoldier";
    setID(id);
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    AScount++;
}
ES* AS::AttackES(GameManager* gameptr, bool Interactive)
{
    ES *EStoAttack = gameptr->getEarthArmy()->RemoveES();
    UAP = (Power * Health / 100.0) / sqrt(EStoAttack->getHealth());
    EStoAttack->setHealth(EStoAttack->getHealth() - UAP);
    if (EStoAttack->getHealth() < 0) {
        EStoAttack->setHealth(0);
    }

    if (EStoAttack->getTA() == 0) {
        EStoAttack->setTA(gameptr->getCurrentTimeStep());
        EStoAttack->setDF(EStoAttack->getTA() - EStoAttack->getTJ());
    }
    if(EStoAttack->getHealth()<0) EStoAttack->setHealth(0);
    if (Interactive) cout << *EStoAttack;
    if (EStoAttack->getHealth() == 0) {
        gameptr->MoveToKilledList(EStoAttack);
        if(EStoAttack->getIsInfected()==true)
        {
            gameptr->getEarthArmy()->decrementInfected_count();
        }
        EStoAttack= nullptr;
    } else if (EStoAttack->getHealth() <= 0.2 * EStoAttack->getInitialHealth()) {
        if(EStoAttack->getIsInfected()==true)
        {
            gameptr->getEarthArmy()->decrementInfected_count();
        }
        gameptr->MoveToSoldiersUML(EStoAttack, 100 - EStoAttack->getHealth());
        EStoAttack= nullptr;
    }
    return EStoAttack;
}
SU* AS::AttackSU(GameManager *gameptr, bool Interactive)
{
    SU* SUtoAttack = gameptr->getAllyArmy()->RemoveSU();
    UAP = (Power * Health / 100.0) / sqrt(SUtoAttack->getHealth());
    SUtoAttack->setHealth(SUtoAttack->getHealth() - UAP);
    if (SUtoAttack->getHealth() < 0) {
        SUtoAttack->setHealth(0);
    }

    if (Interactive) cout << *SUtoAttack;
    if (SUtoAttack->getTA() == 0) {
        SUtoAttack->setTA(gameptr->getCurrentTimeStep());
        SUtoAttack->setDF(SUtoAttack->getTA() - SUtoAttack->getTJ());
    }
    if (SUtoAttack->getHealth() == 0) {
        gameptr->MoveToKilledList(SUtoAttack);
        SUtoAttack= nullptr;
    }
    return SUtoAttack;
}
AS::AS(int h, int p,int ac) {
    Type="AlienSoldier";

    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
}

void AS::Attack(GameManager* gameptr)
{
    LinkedQueue<ES*>* tempESList=new LinkedQueue<ES*>;
    LinkedQueue<SU*>* tempSUList= new LinkedQueue<SU*>;
    int NumofAttacks;
    int EScount=gameptr->getEarthArmy()->getESQueue()->getCount();
    bool Interactive=gameptr->getInteractive();
    int SUcount=gameptr->getAllyArmy()->getNumOfSaverUnits();

    if(!(gameptr->isCallSavers())||SUcount==0) {
        if (EScount == 0) {
            return;
        } else if (EScount >= AttackCapacity) {
            NumofAttacks = AttackCapacity;
        } else if (EScount < AttackCapacity) {
            NumofAttacks = EScount;
        }



        for (int i = 0; i < NumofAttacks; i++)
        {
            ES* es= AttackES(gameptr,Interactive);
            if(es!= nullptr)
                tempESList->enqueue(es);
        }
    }
    else
    {
        if (SUcount == 0) {
            return;
        } else if (SUcount >= AttackCapacity) {
            NumofAttacks = AttackCapacity;
        } else if (SUcount < AttackCapacity) {
            NumofAttacks = SUcount;
        }



        for (int i = 0; i < NumofAttacks; i++)
        {
            SU* su= AttackSU(gameptr,Interactive);
             if(su!= nullptr){
                tempSUList->enqueue(su);
            }

        }
        if(NumofAttacks<AttackCapacity&& gameptr->getAllyArmy()->getNumOfSaverUnits()==0)
        {
            int NumofAttacks2=0;
            if(EScount==0)
            {
                return;
            }
            else if(EScount<AttackCapacity-NumofAttacks)
                NumofAttacks2=EScount;
            else
                NumofAttacks2=AttackCapacity-NumofAttacks;
            for(int i=0;i<NumofAttacks2;i++)
            {
                ES* es= AttackES(gameptr,Interactive);
                if(es!= nullptr)
                    tempESList->enqueue(es);
            }

        }
    }
    ES* tempES;
        while(tempESList->dequeue(tempES))
            gameptr->getEarthArmy()->AddES(tempES);
    SU* tempSU;
    while(tempSUList->dequeue(tempSU))
        gameptr->getAllyArmy()->AddSU(tempSU);

    delete tempSUList;
    delete tempESList;
}