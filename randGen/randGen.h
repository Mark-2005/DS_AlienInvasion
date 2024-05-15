//
// Created by ahmed on 07/04/2024.
//
#include "../Units/Unit.h"
#include "../GameManager/GameManager.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;
#ifndef DS_ALIENINVASION_RANDGEN_H
#define DS_ALIENINVASION_RANDGEN_H

class GameManager;
class SU;

class randGen {
private:
        GameManager*Game;
        int NumOfUnits, ESPer, ETPer, EGPer, ASPer, AMPer, ADPer, Prob, HUPer, VirusProb, SUPer;
        int EarthMinPower, EarthMaxPower, EarthMinHealth, EarthMaxHealth, EarthMinAttCap, EarthMaxAttCap;
        int AlienMinPower, AlienMaxPower, AlienMinHealth, AlienMaxHealth, AlienMinAttCap, AlienMaxAttCap;


public:
        randGen(GameManager*);

        void setNumOfUnits(int);
        void setESPer(int);
        void setETPer(int);
        void setEGPer(int);
        void setHUPer(int);
        void setSUPer(int);
        void setASPer(int);
        void setAMPer(int);
        void setADPer(int);
        void setProb(int);

        void setEarthMinPower(int);
        void setEarthMaxPower(int);
        void setEarthMinHealth(int);
        void setEarthMaxHealth(int);
        void setEarthMinAttCap(int);
        void setEarthMaxAttCap(int);
        void setAlienMinPower(int);
        void setAlienMaxPower(int);
        void setAlienMinHealth(int);
        void setAlienMaxHealth(int);
        void setAlienMinAttCap(int);
        void setAlienMaxAttCap(int);

        int randomNum(int,int);
        int randomAB();
        int randomEH();
        int randomEP();
        int randomEAC();
        int randomAH();
        int randomAP();
        int randomAAC();

        ES* CreateES();
        EG* CreateEG();
        ET* CreateET();
        HU* CreateHU();
        AS* CreateAS();
        AD* CreateAD();
        AM* CreateAM();
        SU* CreateSU();

        void CreateUnitsPerTimeStep();

    void setVirusProb(int virusProb);

};

#endif //DS_ALIENINVASION_RANDGEN_H