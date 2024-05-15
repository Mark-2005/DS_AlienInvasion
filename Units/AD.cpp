//
// Created by ahmed on 06/03/2024.
//
#include "../GameManager/GameManager.h"
#include "AD.h"
#include"cmath"

int AD::ADcount=0;
AD::AD(int id, int h, int p, int ac) {
    Type="AlienDrone";
    setID(id);
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    ADcount++;
}

AD::AD(int h, int p, int ac) {
    Type="AlienDrone";

    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);

}

ET* AD::AttackET(GameManager *gameptr, int TS, bool Interactive) {
    ET* ETToAttack= gameptr->getEarthArmy()->RemoveET();
    UAP=(Power*Health/100)/sqrt(ETToAttack->getHealth());

    int initialHealth=ETToAttack->getInitialHealth();
    ETToAttack->setHealth(ETToAttack->getHealth()-UAP);
    if (ETToAttack->getHealth()<0) ETToAttack->setHealth(0);

    if(ETToAttack->getTA()==0)
    {
        ETToAttack->setTA(TS);
        ETToAttack->setDF(TS-ETToAttack->getTJ());
    }

    if(Interactive) cout<<*ETToAttack<<" ";

    return ETToAttack;
}

EG* AD::AttackEG(GameManager *gameptr, int TS, bool Interactive) {
    EG* EGToAttack= gameptr->getEarthArmy()->RemoveEG();
    UAP=(Power*Health/100.0)/sqrt(EGToAttack->getHealth());
    EGToAttack->setHealth(EGToAttack->getHealth()-UAP);
    if (EGToAttack->getHealth()<0) EGToAttack->setHealth(0);

    if(EGToAttack->getTA()==0)
    {
        EGToAttack->setTA(TS);
        EGToAttack->setDF(TS-EGToAttack->getTJ());
    }

    if(EGToAttack->getHealth()==0)
        gameptr->MoveToKilledList(EGToAttack);

    if(Interactive) cout<<*EGToAttack<<" ";
    return EGToAttack;
}

void AD::Attack(GameManager *gameptr,int AttackWho) {
    int TS=gameptr->getCurrentTimeStep();
    bool Interactive=gameptr->getInteractive();
    LinkedQueue<ET*>* ETTempList= new LinkedQueue<ET*>;
    LinkedQueue<EG*>* EGTempList= new LinkedQueue<EG*>;

    if(AttackWho==1){
        for(int i=0;i<AttackCapacity;i++){
                if (gameptr->getEarthArmy()->getETStack()->getCount() == 0) {
                    if (gameptr->getEarthArmy()->getEGPriQueue()->GetCount() == 0)
                    {
                        break;

                    } else
                    {
                        EG* AttackedEG= AttackEG(gameptr,TS,Interactive);
                        if(AttackedEG->getHealth()>0) EGTempList->enqueue(AttackedEG);
                    }
                } else {
                    ET *AttackedET = AttackET(gameptr, TS, Interactive);
                    if(AttackedET->getHealth()==0) gameptr->MoveToKilledList(AttackedET);
                    else if(AttackedET->getHealth()<0.2*AttackedET->getInitialHealth()) gameptr->MoveToTanksUML(AttackedET);
                    else ETTempList->enqueue(AttackedET);
                }
        }
    } else {
        for (int i = 0; i < AttackCapacity; i++) {
            if (gameptr->getEarthArmy()->getEGPriQueue()->GetCount() == 0) {
                if (gameptr->getEarthArmy()->getETStack()->getCount() == 0)
                    break;
                else {
                    ET *AttackedET = AttackET(gameptr, TS, Interactive);
                    if (AttackedET->getHealth() == 0) gameptr->MoveToKilledList(AttackedET);
                    else if (AttackedET->getHealth() < 0.2 * AttackedET->getInitialHealth())
                        gameptr->MoveToTanksUML(AttackedET);
                    else ETTempList->enqueue(AttackedET);
                }
            } else {
                EG *AttackedEG = AttackEG(gameptr, TS, Interactive);
                if (AttackedEG->getHealth() > 0) EGTempList->enqueue(AttackedEG);
            }
        }
    }

    ET* ptr; EG*EGptr;
    while (ETTempList->dequeue(ptr)){
       gameptr->getEarthArmy()->AddET(ptr);
    }

    while (EGTempList->dequeue(EGptr)){
        gameptr->getEarthArmy()->AddEG(EGptr);
    }
    delete ETTempList;
    delete EGTempList;
}