//
// Created by ahmed on 06/03/2024.
//

#include "AM.h"
#include "../GameManager/GameManager.h"
#include"cmath"
#include"SU.h"
#include "ES.h"
#include "ET.h"
int AM::AMcount=0;

AM::AM(int id, int h, int p, int ac, bool v) {
    Type="AlienMonster";
    setID(id);
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    Virus=v;
    AMcount++;
}
SU* AM::AttackSU(GameManager *gameptr, bool Interactive)
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
ES* AM::AttackES(GameManager *gameptr,bool Interactive) {
    ES* es=gameptr->getEarthArmy()->RemoveES();
    int initialEshealth=es->getInitialHealth();
    int finalEshealth;
    bool done=false;

        UAP=(Power*Health/100.0) / sqrt(es->getHealth());
        es->setHealth(es->getHealth() - UAP);
        if(es->getTA()==0)
        {
            es->setTA(gameptr->getCurrentTimeStep());
            es->setDF(es->getTA()-es->getTJ());
        }
        finalEshealth=es->getHealth();
        if (finalEshealth<0)
        {
            finalEshealth=0;
            es->setHealth(0);
        }

        if(finalEshealth==0)
        {
            gameptr->MoveToKilledList(es);
            done=true;
            if(es->getIsInfected()==true)
                gameptr->getEarthArmy()->decrementInfected_count();
        }
        if(finalEshealth>0&&finalEshealth<=initialEshealth*(20.0/100.0)) {
            gameptr->MoveToSoldiersUML(es, 100 - finalEshealth);
            if(es->getIsInfected()==true)
            {
                gameptr->getEarthArmy()->decrementInfected_count();
            }
            done = true;

        }


    if(Virus==true&&es->getIsImmune()==false)
    {
        es->setIsInfected(true);
        gameptr->IncrementTotalInfectedES();
        gameptr->getEarthArmy()->incrementInfected_count();
    }
    if(Interactive) cout<<*es;
    if(done)
        return nullptr;
    else
        return es;
}

ET* AM::AttackET(GameManager *gameptr, bool Interactive) {
    ET* et=gameptr->getEarthArmy()->RemoveET();
    int initialEthealth=et->getInitialHealth();
    int finalEthealth;
    UAP=(Power*Health/100.0) / sqrt(et->getHealth());
    bool done=false;
    et->setHealth(et->getHealth() - UAP);
    if(et->getTA()==0)
    {
        et->setTA(gameptr->getCurrentTimeStep());
        et->setDF(et->getTA()-et->getTJ());
    }
    finalEthealth=et->getHealth();
    if(finalEthealth<0)
    {
        finalEthealth=0;
        et->setHealth(0);
    }
    if (finalEthealth==0) {
        gameptr->MoveToKilledList(et);
        done=true;
    }
    if(finalEthealth>0&&finalEthealth<=initialEthealth*20.0/100.0)
    {
        gameptr->MoveToTanksUML(et);
        done=true;
    }
    if(Interactive) cout<<*et<<" ";

    if(done) return nullptr;
    else return et;
}

void AM::Attack(GameManager *gameptr)
{
    ES*es;ET*et;SU* su;
    LinkedQueue<SU*>* tempSulist=new LinkedQueue<SU*>;
    LinkedQueue<ET*>* tempEtlist=new LinkedQueue<ET*>;
    LinkedQueue<ES*>* tempEslist=new LinkedQueue<ES*>;

    bool Interactive=gameptr->getInteractive();
    bool attackSu=false;

        for (int i = 0; i < AttackCapacity; i++) {
            if (i <= ceil(AttackCapacity / 2.0)) {
                int SUcount=gameptr->getAllyArmy()->getNumOfSaverUnits();

                if(gameptr->isCallSavers()&&SUcount!=0)
                    attackSu=true;
                else attackSu=false;

                if (gameptr->getEarthArmy()->getESQueue()->getCount() == 0) {
                    if (gameptr->getEarthArmy()->getETStack()->getCount() == 0)
                        break;
                    else {
                        et= AttackET(gameptr, Interactive);
                        if (et!= nullptr)
                            tempEtlist->enqueue(et);
                    }
                } else {
                    if (attackSu == false) {
                        es = AttackES(gameptr, Interactive);
                        if (es != nullptr)
                            tempEslist->enqueue(es);
                    }
                    else
                    {
                        su= AttackSU(gameptr,Interactive);
                        if(su!= nullptr)
                            tempSulist->enqueue(su);
                    }
                }
            } else {
                if (gameptr->getEarthArmy()->getETStack()->getCount() == 0) {
                    if (gameptr->getEarthArmy()->getESQueue()->getCount() == 0)
                        break;
                    else {
                        if (attackSu == false) {
                            es = AttackES(gameptr, Interactive);
                            if (es != nullptr)
                                tempEslist->enqueue(es);
                        }
                        else
                        {
                            su= AttackSU(gameptr,Interactive);
                            if(su!= nullptr)
                                tempSulist->enqueue(su);
                        }
                    }
                } else {
                    et = AttackET(gameptr, Interactive);
                    if (et != nullptr)
                        tempEtlist->enqueue(et);
                }
            }
        }

    int tempEslistcount=tempEslist->getCount();
    for(int i=0;i<tempEslistcount;i++)
    {
        tempEslist->dequeue(es);
        gameptr->getEarthArmy()->AddES(es);
    }

    int tempEtlistcount=tempEtlist->getCount();
    for(int i=0;i<tempEtlistcount;i++)
    {
        tempEtlist->dequeue(et);
        gameptr->getEarthArmy()->AddET(et);
    }

    int tempSulidtcount=tempSulist->getCount();
    for(int i=0;i<tempSulidtcount;i++)
    {
        tempSulist->dequeue(su);
        gameptr->getAllyArmy()->AddSU(su);
    }
    delete tempEtlist;
    delete tempEslist;
    delete tempSulist;
}

bool AM::isVirus() const {
    return Virus;
}
