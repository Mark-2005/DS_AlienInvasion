//
// Created by DELL on 16/04/2024.
//

#include "HU.h"
#include "cmath"
#include "../GameManager/GameManager.h"

int HU::HUcount=0;
HU::HU(int id, int h, int p,int ac) {
    Type="HealUnit";
    setID(id);
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    HUcount++;
}


HU::HU(int h, int p,int ac) {
    Type="HealUnit";

    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
}


void HU::Attack(GameManager* pGame)
{
    int healCountPerTimeStep=0;
    priQueue<ES*>* tempHealSol= new priQueue<ES*>;
    LinkedQueue<ET*>* tempHealTank=new LinkedQueue<ET*>;
    EarthArmy* EArmy=pGame->getEarthArmy();
    int dummyPri;
    bool DidHeal=false;
    bool FirstToHeal=true;
    bool FailedToHeal=false;
    ES* CurrentHealSol;
    ET* CurrentHealTank;
    bool interactive= pGame->getInteractive();
    while(pGame->GetSoldiersUML()->dequeue(CurrentHealSol,dummyPri))
    {
        if (pGame->getCurrentTimeStep() - CurrentHealSol->GetTH() >= 10)
        {
            pGame->MoveToKilledList(CurrentHealSol);
        }
        else
            tempHealSol->enqueue(CurrentHealSol,dummyPri);
    }
    while(tempHealSol->dequeue(CurrentHealSol,dummyPri))
    {
        pGame->GetSoldiersUML()->enqueue(CurrentHealSol,dummyPri);
    }
    while(pGame->GetTanksUML()->dequeue(CurrentHealTank))
    {
        if (pGame->getCurrentTimeStep() - CurrentHealTank->GetTH() >= 10)
        {
            pGame->MoveToKilledList(CurrentHealTank);
        }
        else
            tempHealTank->enqueue(CurrentHealTank);
    }
    while(tempHealTank->dequeue(CurrentHealTank))
    {
        pGame->GetTanksUML()->enqueue(CurrentHealTank);
    }
    // &&(!pGame->GetSoldiersUML()->isEmpty()&&!pGame->GetTanksUML()->isEmpty())
    while(healCountPerTimeStep<AttackCapacity)
    {
        if(!pGame->GetSoldiersUML()->isEmpty())
        {
            pGame->GetSoldiersUML()->dequeue(CurrentHealSol,dummyPri);
            if(CurrentHealSol->getIsInfected()==false)
            {
                if (FirstToHeal && interactive) {
                    cout << "HU " << this->getID() << " Heals [ ";
                    FirstToHeal=false;
                }
                const int OldHealth = CurrentHealSol->getHealth();
                CurrentHealSol->setHealth(
                        OldHealth + static_cast<int>(Power * (static_cast<float>(Health) / 100.0)) / sqrt(Health));
                DidHeal = true;
                if (CurrentHealSol->getHealth() > 0.2 * (CurrentHealSol->getInitialHealth())) {
                    EArmy->AddES(CurrentHealSol);
                } else {
                    tempHealSol->enqueue(CurrentHealSol, 100 - CurrentHealSol->getHealth());
                }
                if (interactive) cout << *CurrentHealSol << " ";
            }
            else
            {
                if (FirstToHeal && interactive) {
                    cout << "HU " << this->getID() << " Heals [ ";
                    FirstToHeal=false;
                }
                const int OldHealth = CurrentHealSol->getHealth();
                CurrentHealSol->setHealth(OldHealth + static_cast<int>(Power * (static_cast<float>(Health) / 100.0)) / sqrt(Health));
                DidHeal = true;

                tempHealSol->enqueue(CurrentHealSol, 100 - CurrentHealSol->getHealth());

                CurrentHealSol->setIsInfected(false);
                CurrentHealSol->setIsImmune(true);
                if (interactive) cout << *CurrentHealSol << " ";
            }
        } else if(!pGame->GetTanksUML()->isEmpty())
        {
            pGame->GetTanksUML()->dequeue(CurrentHealTank);
            if (FirstToHeal && interactive) {
                cout << "HU " << this->getID() << " Heals [ ";
                FirstToHeal=false;
            }
            int OldHealth = CurrentHealTank->getHealth();
            CurrentHealTank->setHealth(OldHealth +  static_cast<int>(Power * (static_cast<float>(Health) / 100.0)) / sqrt(Health));
            DidHeal=true;
            if (CurrentHealTank->getHealth() > 0.2*(CurrentHealTank->getInitialHealth()))
            {
                EArmy->AddET(CurrentHealTank);
            } else
            {
                tempHealTank->enqueue(CurrentHealTank);
            }
            if (interactive) cout<<*CurrentHealTank<<" ";
        }
        healCountPerTimeStep++;
    }
    while(!tempHealSol->isEmpty())
    {
        tempHealSol->dequeue(CurrentHealSol,dummyPri);
        pGame->MoveToSoldiersUML(CurrentHealSol,dummyPri);
    }

    while(tempHealTank->dequeue(CurrentHealTank))
    {
        pGame->MoveToTanksUML(CurrentHealTank);
    }

    if(DidHeal)
    {
        pGame->MoveToKilledList(this);
        if (interactive) cout<<"]"<<endl;
    }
    else
    {
        if(interactive)
            cout <<"No Enough Tanks Or Soldiers To Heal"<<endl;
        EArmy->AddHU(this);
    }
}
