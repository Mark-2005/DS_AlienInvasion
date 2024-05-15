#include "ET.h"
#include "../GameManager/GameManager.h"
#include <cmath>

using namespace std;
int ET::ETcount=0;
ET::ET(int id, int h, int p,int ac):initialHealth(h) {
    Type="EarthTank";
    setID(id);
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    ETcount++;
}


//ET::ET(int h, int p,int ac) {
//    Type="EarthTank";
//
//    setHealth(h);
//    setPower(p);
//    setAttackCapacity(ac);
//}
AM* ET::AttackAm(GameManager *gameptr, bool Interactive)
{
    AM* am=gameptr->getAlienArmy()->RemoveAM();
    UAP= (Power* Health/100 )/sqrt(am->getHealth());
    am->setHealth(am->getHealth() - UAP);

    if(am->getTA()==0)
    {
        am->setTA(gameptr->getCurrentTimeStep());
        am->setDF(am->getTA()-am->getTJ());
    }

    if (am->getHealth()<0) am->setHealth(0);

    if(Interactive) cout<<*am<<" ";

    if (am->getHealth() == 0) {
        gameptr->MoveToKilledList(am);
        am= nullptr;
    }

    return am;
}
AS* ET::AttackAs(GameManager *gameptr, bool Interactive)
{
    AS* as=gameptr->getAlienArmy()->RemoveAS();
    UAP= (Power* Health/100 )/sqrt(as->getHealth());
    as->setHealth(as->getHealth() - UAP);
    if(as->getTA()==0)
    {
        as->setTA(gameptr->getCurrentTimeStep());
        as->setDF(as->getTA()-as->getTJ());
    }

    if (as->getHealth()<0) as->setHealth(0);

    if (Interactive) cout<<*as<<" ";

    if (as->getHealth() == 0)
    {
        gameptr->MoveToKilledList(as);
        as= nullptr;
    }


    return as;
}
void ET::SetTH(int th)
{
    TH=th;
}
int ET::GetTH() const
{
    return TH;
}

void ET::Attack(GameManager* gameptr)
{
    LinkedQueue<AS*>* tempAslist=new LinkedQueue<AS*>;
    LinkedQueue<AM*>* tempAmlist=new LinkedQueue<AM*>;
    AS* as;
    AM* am;

    bool Interactive= gameptr->getInteractive();
    bool AttackAS=gameptr->getETAttacksAS();

    int NumofAm;

    for(int i=0;i<AttackCapacity;i++) {
        NumofAm=gameptr->getAlienArmy()->getMonstersArr()->getCount();
        int NumofES = gameptr->getEarthArmy()->getESQueue()->getCount();
        int NumofAS = gameptr->getAlienArmy()->getASQueue()->getCount();
        int ASnum30per=ceil(NumofAS*30.0/100.0);
        int ASnum80per=ceil(NumofAS*80.0/100.0);
        if (AttackAS){
            if (NumofES >= ASnum80per)
            {
                AttackAS=false;
                gameptr->setETAttacksAS(AttackAS);
            }
        } else {
            if (NumofES <ASnum30per&& NumofAS>0)
            {
                AttackAS=true;
                gameptr->setETAttacksAS(AttackAS);
            }
        }

        if(AttackAS==false&&NumofAm==0) break;
        if(AttackAS)
        {
            as=AttackAs(gameptr,Interactive);
            if(as!= nullptr)
                tempAslist->enqueue(as);
        }
        else
        {
            NumofAm=gameptr->getAlienArmy()->getMonstersArr()->getCount();
            if ( NumofAm> 0)
            {
                am=AttackAm(gameptr,Interactive);
                if(am!= nullptr)
                    tempAmlist->enqueue(am);
            }
        }

    }

    int tempAscount=tempAslist->getCount();
    for(int j=0;j<tempAscount;j++)
    {
        tempAslist->dequeue(as);
        gameptr->getAlienArmy()->AddAS(as);
    }

    int tempAmcount=tempAmlist->getCount();
    for(int j=0;j<tempAmcount;j++)
    {
        tempAmlist->dequeue(am);
        gameptr->getAlienArmy()->AddAM(am);
    }

    delete tempAmlist;
    delete tempAslist;

}

int ET::getInitialHealth() const {return initialHealth;}