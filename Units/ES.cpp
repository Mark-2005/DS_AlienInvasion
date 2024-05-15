//
// Created by ahmed on 04/04/2024.
//
#include "../GameManager/GameManager.h"
#include "ES.h"
#include "cmath"

int ES::EScount=0;

ES::ES(int id, int h, int p,int ac):initialHealth(h) {
    Type="EarthSoldier";
    setID(id);
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    EScount++;
}

//ES::ES(int h, int p,int ac) {
//    Type="EarthSoldier";
//
//    setHealth(h);
//    setPower(p);
//    setAttackCapacity(ac);
//}

int ES::GetTH() const
{
    return TH;
}
void ES::SetTH(int th)
{
    TH=th;
}

void ES::Attack(GameManager* gameptr)
{
    if(IsInfected==false) {
        bool Interactive = gameptr->getInteractive();
        int NumofAttacks;
        int AScount = gameptr->getAlienArmy()->getASQueue()->getCount();

        if (AScount == 0) {
            if (Interactive == true) cout << "No enough AS exist to be attacked";
            return;
        } else if (AScount >= AttackCapacity) {
            NumofAttacks = AttackCapacity;
        } else if (AScount < AttackCapacity) {
            NumofAttacks = AScount;
        }

        LinkedQueue<AS *> *tempList = new LinkedQueue<AS *>;

        for (int i = 0; i < NumofAttacks; i++) {
            AS *AStoAttack = gameptr->getAlienArmy()->RemoveAS();
            UAP = (Power * Health / 100.0) / sqrt(AStoAttack->getHealth());
            AStoAttack->setHealth(AStoAttack->getHealth() - UAP);
            if (AStoAttack->getTA() == 0) {
                AStoAttack->setTA(gameptr->getCurrentTimeStep());
                AStoAttack->setDF(gameptr->getCurrentTimeStep() - AStoAttack->getTJ());
            }

            if (AStoAttack->getHealth() <= 0) {
                AStoAttack->setHealth(0);
            }

            if (AStoAttack->getHealth() == 0) {
                gameptr->MoveToKilledList(AStoAttack);
            } else {
                tempList->enqueue(AStoAttack);
            }
            if (Interactive == true) cout << *AStoAttack << " ";
        }

        AS *tempAS;
        while (tempList->dequeue(tempAS)) gameptr->getAlienArmy()->AddAS(tempAS);

        delete tempList;
    } else {
        int NumofAttacks;
        int EScount=gameptr->getEarthArmy()->getESQueue()->getCount();
        bool Interactive=gameptr->getInteractive();

        if(EScount==0)
        {
            return;
        }
        else if(EScount>=AttackCapacity)
        {
            NumofAttacks=AttackCapacity;
        }

        else if(EScount<AttackCapacity)
        {
            NumofAttacks=EScount;
        }

        LinkedQueue <ES*> tempList;

        for (int i=0;i<NumofAttacks;i++)
        {
            ES* EStoAttack=gameptr->getEarthArmy()->RemoveES();
            UAP=(Power*Health/100.0)/sqrt(EStoAttack->getHealth());
            EStoAttack->setHealth(EStoAttack->getHealth()-UAP);
            if(EStoAttack->getHealth()<0)
            {
                EStoAttack->setHealth(0);
            }

            if(EStoAttack->getTA()==0){
                EStoAttack->setTA(gameptr->getCurrentTimeStep());
                EStoAttack->setDF(EStoAttack->getTA()-EStoAttack->getTJ());
            }
            if(EStoAttack->getHealth()==0)
            {
                gameptr->MoveToKilledList(EStoAttack);
                gameptr->getEarthArmy()->decrementInfected_count();
            } else if(EStoAttack->getHealth()<=0.2*EStoAttack->getInitialHealth()){
                gameptr->MoveToSoldiersUML(EStoAttack,100-EStoAttack->getHealth());
                gameptr->getEarthArmy()->decrementInfected_count();

            } else {
                tempList.enqueue(EStoAttack);
            }
            if (Interactive) cout<<*EStoAttack;
        }
        ES* tempES;
        while(tempList.dequeue(tempES)) gameptr->getEarthArmy()->AddES(tempES);
    }
}

int ES::getInitialHealth() const {return initialHealth;}

bool ES::getIsInfected() const {return IsInfected;}

void ES::setIsInfected(bool isInfected) {IsInfected = isInfected;}

bool ES::getIsImmune() const { return IsImmune;}

void ES::setIsImmune(bool isImmune) {IsImmune = isImmune;}

void ES::SpreadInfection(ES* es)
{
    if(es){
        es->setIsInfected(true);
    }
}