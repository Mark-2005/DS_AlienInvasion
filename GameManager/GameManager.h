//
// Created by ahmed on 05/04/2024.
//

#pragma once

#include "../Armies/EarthArmy.h"
#include "../Armies/AlienArmy.h"
#include "../Armies/AllyArmy.h"
#include "../DataStructures/QueueADT.h"
#include "../DataStructures/Queue.h"
#include "../Units/Unit.h"
#include <fstream>
#include <iostream>
#include "../DataStructures/PriorityQueue.h"

class randGen;
class GameManager {
private:
    int TimeStep;
    int ThresholdAllyarmy;
    int TotalInfectedSoldiers=0;
    bool Interactive;
    LinkedQueue<Unit*>* KilledList;
    randGen* Generator;
    EarthArmy Fighters;
    AlienArmy Traitors;
    AllyArmy Savers;
    bool CallSavers=false;
public:
    bool isCallSavers() const;

    bool isSaversWithdraw() const;

private:
    bool SaversWithdraw=false;
    bool ETAttacksAS=false;
    bool win=false;
    priQueue<ES*>* SoldiersUML;
    LinkedQueue<ET*>* TanksUML;
public:

    int RandomAB();
    GameManager();
    ~GameManager();
    void ReadInputParameters();
    int getCurrentTimeStep();
    bool MoveToKilledList(Unit*);
    EarthArmy* getEarthArmy();
    AlienArmy* getAlienArmy();
    AllyArmy* getAllyArmy();
    int getThresholdAllyarmy() const;
    void setThresholdAllyarmy(int thresholdAllyarmy);
    bool getInteractive();
    bool getETAttacksAS();
    void setETAttacksAS(bool AttackAS);

    priQueue<ES*>* GetSoldiersUML();
    LinkedQueue<ET*>* GetTanksUML();
    void MoveToSoldiersUML(ES* UnitToHeal,int HealPri);
    void MoveToTanksUML(ET* UnitToHeal);
    void Phase1TestCode();
    void PrintKilledList();
    void PrintUML();
    void Attack();
    void Simulate();
    void OutputFile();
    bool BattleDone();
    void IncrementTotalInfectedES();
};


 //DS_ALIENINVASION_GAMEMANAGER_H
