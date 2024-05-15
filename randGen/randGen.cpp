//
// Created by ahmed on 07/04/2024.
//
#include "../GameManager/GameManager.h"
#include "randGen.h"


randGen::randGen(GameManager* Gameptr)
{
    static int counter=0;
    counter++;

    time_t seed = time(NULL)+counter;
    srand(seed);

    Game=Gameptr;

}

void randGen::setNumOfUnits(int Num){NumOfUnits=Num;}
void randGen::setESPer(int ES){ESPer=ES;}
void randGen::setETPer(int ET){ETPer=ET;}
void randGen::setEGPer(int EG){EGPer=EG;}
void randGen::setHUPer(int HU){HUPer=HU;}
void randGen::setSUPer(int SU){SUPer=SU;}
void randGen::setASPer(int AS){ASPer=AS;}
void randGen::setAMPer(int AM){AMPer=AM;}
void randGen::setADPer(int AD){ADPer=AD;}
void randGen::setProb(int P){Prob=P;}

void randGen::setVirusProb(int virusProb) {VirusProb = virusProb;}

void randGen::setEarthMinPower(int MinPower){EarthMinPower=MinPower;}
void randGen::setEarthMaxPower(int MaxPower){EarthMaxPower=MaxPower;}
void randGen::setEarthMinHealth(int MinHealth){EarthMinHealth=MinHealth;}
void randGen::setEarthMaxHealth(int MaxHealth){EarthMaxHealth=MaxHealth;}
void randGen::setEarthMinAttCap(int MinAttCap){EarthMinAttCap=MinAttCap;}
void randGen::setEarthMaxAttCap(int MaxAttCap){EarthMaxAttCap=MaxAttCap;}
void randGen::setAlienMinPower(int MinPower){AlienMinPower=MinPower;}
void randGen::setAlienMaxPower(int MaxPower){AlienMaxPower=MaxPower;}
void randGen::setAlienMinHealth(int MinHealth){AlienMinHealth=MinHealth;}
void randGen::setAlienMaxHealth(int MaxHealth){AlienMaxHealth=MaxHealth;}
void randGen::setAlienMinAttCap(int MinAttCap){AlienMinAttCap=MinAttCap;}
void randGen::setAlienMaxAttCap(int MaxAttCap){AlienMaxAttCap=MaxAttCap;}

int randGen::randomNum(int max,int min) {
    int randomNumber = rand() % (max+1 - min) + min;
    return randomNumber;
}

int randGen::randomAB()
{
    int randomAB= rand()%(100+1-1)+1;
    return randomAB;
}

int randGen::randomEH() {
    int randomNumberEH = rand() % (EarthMaxHealth + 1 - EarthMinHealth) + EarthMinHealth;
    return randomNumberEH;
}

int randGen::randomEP() {
    int randomNumberEP = rand() % (EarthMaxPower + 1 - EarthMinPower) + EarthMinPower;
    return randomNumberEP;
}

int randGen::randomEAC() {
    int randomNumberEAC = rand() % (EarthMaxAttCap + 1 - EarthMinAttCap) + EarthMinAttCap;
    return randomNumberEAC;
}

int randGen::randomAH() {
    int randomNumberAH = rand() % (AlienMaxHealth + 1 - AlienMinHealth) + AlienMinHealth;
    return randomNumberAH;
}

int randGen::randomAP() {
    int randomNumberAP = rand() % (AlienMaxPower + 1 - AlienMinPower) + AlienMinPower;
    return randomNumberAP;
}

int randGen::randomAAC() {
    int randomNumberAAC = rand() % (AlienMaxAttCap+1 - AlienMinAttCap) + AlienMinAttCap;
    return randomNumberAAC;
}


ES* randGen::CreateES()
{
    ES*NewES=new ES(Game->getEarthArmy()->getNextID(),randomEH(),randomEP(),randomEAC());
    Game->getEarthArmy()->incrementNextID();

    return NewES;
}

EG* randGen::CreateEG(){
    EG*NewEG=new EG(Game->getEarthArmy()->getNextID(),randomEH(),randomEP(),randomEAC());
    Game->getEarthArmy()->incrementNextID();

    return NewEG;
}

HU* randGen::CreateHU(){
    HU*NewHU=new HU(Game->getEarthArmy()->getNextID(),randomEH(),randomEP(),randomEAC());
    Game->getEarthArmy()->incrementNextID();

    return NewHU;
}

ET* randGen::CreateET(){
    ET*NewET=new ET(Game->getEarthArmy()->getNextID(),randomEH(),randomEP(),randomEAC());
    Game->getEarthArmy()->incrementNextID();

    return NewET;
}

AS* randGen::CreateAS()
{
    AS*NewAS=new AS(Game->getAlienArmy()->getNextID(),randomAH(),randomAP(),randomAAC());
    Game->getAlienArmy()->incrementNextID();

    return NewAS;
}

AD* randGen::CreateAD()
{
    AD*NewAD=new AD(Game->getAlienArmy()->getNextID(),randomAH(),randomAP(),randomAAC());
    Game->getAlienArmy()->incrementNextID();


    return NewAD;
}

AM* randGen::CreateAM()
{
    int num=randomAB();
    bool v;
    v=(num<=VirusProb)?true:false;

        AM *NewAM = new AM(Game->getAlienArmy()->getNextID(), randomAH(), randomAP(), randomAAC(), v);
        Game->getAlienArmy()->incrementNextID();
        return NewAM;
}

SU* randGen::CreateSU()
{
    SU*NewSU=new SU(Game->getAllyArmy()->getNextID(),randomEH(),randomEP(),randomEAC());
    Game->getAllyArmy()->incrementNextID();
    return NewSU;
}

void randGen::CreateUnitsPerTimeStep()
{
    int A = rand() % (101 - 1) + 1;
    int Tj=Game->getCurrentTimeStep();
    if (A<=Prob){
        for(int i=0;i<NumOfUnits;i++){
            int B = rand() % (101 - 1) + 1;
            if(B<=ESPer){
                ES*NewES=CreateES();
                NewES->setTJ(Tj);
                Game->getEarthArmy()->AddES(NewES);
            } else if(B<=(ESPer+ETPer)){
                ET*NewET=CreateET();
                NewET->setTJ(Tj);
                Game->getEarthArmy()->AddET(NewET);
            } else if(B<=(ESPer+ETPer+EGPer)){
                EG*NewEG=CreateEG();
                NewEG->setTJ(Tj);
                Game->getEarthArmy()->AddEG(NewEG);
            } else {
                HU*NewHU=CreateHU();
                NewHU->setTJ(Tj);
                Game->getEarthArmy()->AddHU(NewHU);
            }

            if(B<=ASPer){
                AS*NewAS=CreateAS();
                NewAS->setTJ(Tj);
                Game->getAlienArmy()->AddAS(NewAS);
            } else if(B<=(ASPer+AMPer)){
                AM*NewAM=CreateAM();
                NewAM->setTJ(Tj);
                Game->getAlienArmy()->AddAM(NewAM);
            } else{
                AD*NewAD=CreateAD();
                NewAD->setTJ(Tj);
                Game->getAlienArmy()->AddAD(NewAD);
            }

        }
    }

    if(Game->isCallSavers()&& !(Game->isSaversWithdraw()) && A<=Prob)
    {
        for(int i=0;i<SUPer;i++) {
            SU *NewSU = CreateSU();
            NewSU->setTJ(Tj);
            Game->getAllyArmy()->AddSU(NewSU);
        }
    }
    // Fighters.PrintEarthAliveUnits();
    //Traitors.PrintAlienAliveUnits();
}