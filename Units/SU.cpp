//
// Created by ahmed on 10/05/2024.
//
#include "SU.h"
#include "../GameManager/GameManager.h"
#include"cmath"
int SU::SUcount=0;
SU::SU(int id, int h, int p, int ac) {
    ID=id;
    setHealth(h);
    Power=p;
    AttackCapacity=ac;
    Type="SaverUnit";
    SUcount++;
}

void SU::Attack(GameManager *gameptr) {
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
        if (Interactive == true) cout << *AStoAttack;
    }
}