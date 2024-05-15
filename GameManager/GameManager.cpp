//
// Created by ahmed on 05/04/2024.
//
using namespace std;
#include "GameManager.h"
#include "../randGen/randGen.h"
#include<limits>
#include<cstdio>
#include <iomanip>
GameManager::GameManager()
{
    TimeStep=1;
    KilledList=new LinkedQueue<Unit*>;
    Generator=new randGen(this);
    SoldiersUML=new priQueue<ES*>;
    TanksUML= new LinkedQueue<ET*>;
    cout<<"The whispers have become shouts, the blury fights in the night sky, confirmed spaceships.\n";
    cout<<"Alien Invasion is no longer science fiction!!\n";
    cout<<"The world needs to act quickly to be ready for the invasion!\n";
    cout<<"Luckily, the Global Defense Unit decided to make the world ready by simulating Earth's power against aliens' power.\n";
    ReadInputParameters();
}

GameManager::~GameManager(){
    delete KilledList;
    delete Generator;
    delete SoldiersUML;
    delete TanksUML;
}

void GameManager::ReadInputParameters() {
    int NumOfUnits, ESPer, ETPer, EGPer, ASPer, AMPer, ADPer, Prob, HUPer, VirusProb, SUPer;
    int EarthMinPower, EarthMaxPower, EarthMinHealth, EarthMaxHealth, EarthMinAttCap, EarthMaxAttCap;
    int AlienMinPower, AlienMaxPower, AlienMinHealth, AlienMaxHealth, AlienMinAttCap, AlienMaxAttCap;
    fstream input_file;

    int SimMode;

    do{
        cout<<"Choose the simulation mode: "<<endl;
        cout<<"1: Weak Earth Weak Aliens\n";
        cout<<"2: Weak Earth Moderate Aliens\n";
        cout<<"3: Weak Earth Strong Aliens\n";
        cout<<"4: Strong Earth Weak Aliens\n";
        cout<<"5: Strong Earth Moderate Aliens\n";
        cout<<"6: Strong Earth Strong Aliens\n";
        cin>>SimMode;

        if(SimMode<1||SimMode>6) cout<<"Invalid number entered! Try again\n";
    }while(!(SimMode>=1&& SimMode<=6));

    switch(SimMode) {
        case 1: {input_file.open("../GameManager/Input.txt"); break;}
        case 2:  {input_file.open("../GameManager/Input2.txt"); break;}
        case 3:  {input_file.open("../GameManager/Input3.txt"); break;}
        case 4:  {input_file.open("../GameManager/Input4.txt"); break;}
        case 5:  {input_file.open("../GameManager/Input5.txt"); break;}
        default:  {input_file.open("../GameManager/Input6.txt"); break;}
    }

    if (!input_file.is_open()) {
        cerr << "Error: Unable to open input file " << endl;
        return;
    }

    string line;
    input_file >> NumOfUnits;
    Generator->setNumOfUnits(NumOfUnits);

    getline(input_file,line);
    input_file >> ESPer >> ETPer >> EGPer >>HUPer>>SUPer;

    Generator->setESPer(ESPer); Generator->setETPer(ETPer); Generator->setEGPer(EGPer); Generator->setHUPer(HUPer);
    Generator->setSUPer(SUPer);

    getline(input_file,line);
    input_file >> ASPer >> AMPer >> ADPer;
    Generator->setASPer(ASPer); Generator->setAMPer(AMPer); Generator->setADPer(ADPer);

    getline(input_file,line);
    input_file >> Prob>>VirusProb>>ThresholdAllyarmy;
    Generator->setProb(Prob);
    Generator->setVirusProb(VirusProb);

    getline(input_file,line);
    input_file >> EarthMinPower;
    input_file.ignore();
    input_file>> EarthMaxPower;
    Generator->setEarthMaxPower(EarthMaxPower); Generator->setEarthMinPower(EarthMinPower);

    input_file >> EarthMinHealth;
    input_file.ignore();
    input_file>> EarthMaxHealth;
    Generator->setEarthMaxHealth(EarthMaxHealth); Generator->setEarthMinHealth(EarthMinHealth);

    input_file >> EarthMinAttCap;
    input_file.ignore();
    input_file>> EarthMaxAttCap;
    Generator->setEarthMaxAttCap(EarthMaxAttCap); Generator->setEarthMinAttCap(EarthMinAttCap);

    getline(input_file,line);
    input_file >> AlienMinPower;
    input_file.ignore();
    input_file>>AlienMaxPower;
    Generator->setAlienMaxPower(AlienMaxPower); Generator->setAlienMinPower(AlienMinPower);

    input_file >> AlienMinHealth;
    input_file.ignore();
    input_file>> AlienMaxHealth;
    Generator->setAlienMaxHealth(AlienMaxHealth); Generator->setAlienMinHealth(AlienMinHealth);

    input_file >> AlienMinAttCap;
    input_file.ignore();
    input_file>>AlienMaxAttCap;
    Generator->setAlienMaxAttCap(AlienMaxAttCap); Generator->setAlienMinAttCap(AlienMinAttCap);

    input_file.close();
}

bool GameManager::MoveToKilledList(Unit *unit)
{
    KilledList->enqueue(unit);
    unit->setTD(TimeStep);
    unit->setDD(unit->getTD()-unit->getTA());
    unit->setDB(unit->getTD()-unit->getTJ());
    return true;
}

AlienArmy* GameManager::getAlienArmy() {return &Traitors;}
EarthArmy* GameManager::getEarthArmy() {return &Fighters;}
AllyArmy* GameManager::getAllyArmy() {return &Savers;}

priQueue<ES*>* GameManager::GetSoldiersUML() {return SoldiersUML;}
LinkedQueue<ET*>* GameManager::GetTanksUML() {return TanksUML;}
void GameManager::MoveToSoldiersUML(ES* UnitToHeal,int HealPri)
{
    UnitToHeal->SetTH(TimeStep);
    SoldiersUML->enqueue(UnitToHeal,HealPri);
}

void GameManager::MoveToTanksUML(ET* UnitToHeal)
{
    UnitToHeal->SetTH(TimeStep);
    TanksUML->enqueue(UnitToHeal);
}

int GameManager::getCurrentTimeStep() {return TimeStep;}

bool GameManager::getInteractive() {return Interactive;}

void GameManager::PrintKilledList()
{
    cout<<"=============================Killed/Destructed Units================================="<<endl<<KilledList->getCount()<<" units " <<"\t";
    KilledList->printQueue();
    cout<<endl;
}
void GameManager::PrintUML() {
    cout<<"=============================Unit Maintenance List ================================="<<endl;
    cout<<SoldiersUML->GetCount()<<" Soldiers " <<"\t";
    if (SoldiersUML->isEmpty()) cout<<"[ ]"<<endl;
    SoldiersUML->printPriQueue();
    cout<<endl;
    cout<<TanksUML->getCount()<<" Tanks " <<"\t";
    if (TanksUML->isEmpty()) cout<<"[ ]"<<endl;
    TanksUML->printQueue();
    cout<<endl;
}
void GameManager::Attack()
{
    int Per=Fighters.getPer_Infected();
    Fighters.Attack(this);

    if (Per >= ThresholdAllyarmy && !CallSavers) {
        CallSavers = true;
    }

    if(CallSavers&&!SaversWithdraw){
        Savers.Attack(this);
    }

    Traitors.Attack(this);
    if (Interactive)
        PrintUML();
    Fighters.HealAttack(this);

    if(!SaversWithdraw&&CallSavers){
        if(Fighters.getPer_Infected()==0){
            SaversWithdraw=true;
            CallSavers=false;
            SU *tempsu;
            if (Interactive)
                cout << "all ES recovered So the SU will Withdraw" << endl;
            while (Savers.getSUQueue()->dequeue(tempsu)) {
                MoveToKilledList(tempsu);
            }
        }
    }

}

void GameManager::Phase1TestCode()
{
    do {
        cout<<"Current Timestep "<<TimeStep<<endl;
        Generator->CreateUnitsPerTimeStep();
        int x=Generator->randomAB();
        switch(x){
            case 1 ... 10:
                {
                    if(Fighters.getESQueue()->isEmpty())
                    {
                        cout<<"invalid operation no Earth soldiers Available"<<endl;
                    }
                    else {
                        ES *tempES=Fighters.RemoveES();
                        Fighters.AddES(tempES);
                    }
                }
            break;
            case 11 ... 20:
            {
                if(Fighters.getETStack()->isEmpty())
                {
                    cout<<"invalid operation no Earth Tanks Available"<<endl;
                }
                else {
                    ET* tempET=Fighters.RemoveET();
                    KilledList->enqueue(tempET);
                }
            }
            break;
            case 21 ... 30:
            {
                if(Fighters.getEGPriQueue()->isEmpty())
                {
                    cout<<"invalid operation no Earth Gunnery Available"<<endl;
                }
                else {
                    EG* tempEG=Fighters.RemoveEG();
                    int tempH = tempEG->getHealth();
                    tempEG->setHealth(tempH/2);
                    Fighters.AddEG(tempEG);
                }

            }
                break;
            case 31 ... 40:
            {
                if(Traitors.getASQueue()->getCount()<5)
                {
                    cout<<"invalid operation no Alien Soldiers Available"<<endl;
                }
                else
                {
                    LinkedQueue<AS*> tempList;
                    for(int i=0;i<5;i++)
                    {
                        AS* tempAS=Traitors.RemoveAS();
                        int tempH=tempAS->getHealth();
                        tempH=tempH/2;
                        tempAS->setHealth(tempH);
                        tempList.enqueue(tempAS);
                    }
                    for(int i=0;i<5;i++)
                    {
                        AS* tempAS;
                        tempList.dequeue(tempAS);
                        Traitors.AddAS(tempAS);
                    }
                }
            }
                break;
            case 41 ... 50:
            {
                if (Traitors.getMonstersArr()->getCount() < 5) {
                    cout << "invalid operation no Alien Monsters Available" << endl;
                } else {
                    AM *tempAM[5];
                    for (int i = 0; i < 5; i++) {
                        tempAM[i]=Traitors.RemoveAM();
                    }
                    for (int i = 0; i < 5; i++) {
                        Traitors.AddAM(tempAM[i]);
                    }
                }

            }
                break;
            case 51 ... 60:
            {
                if(Traitors.getADQueue()->getCount()<6)
                {
                    cout<<"invalid operation no Alien Drones Available"<<endl;
                }
                else
                {
                    AD* tempAD[6];
                    for(int i=0;i<6;i+=2)
                    {
                        tempAD[i]=Traitors.RemoveADFront();
                        tempAD[i+1]=Traitors.RemoveADBack();
                    }
                    for(int i=0;i<6;i+=2)
                    {
                        KilledList->enqueue(tempAD[i]);
                        KilledList->enqueue(tempAD[i+1]);
                    }
                }
            }
            break;
            default:
                cout<<"xxxxxxxxxxxxxxxxxxxx no operations to be done in the current time step  xxxxxxxxxxxxxxxxxxxxxxx"<<endl;

        }

        Fighters.PrintEarthAliveUnits();
        Traitors.PrintAlienAliveUnits();
        PrintKilledList();
        PrintUML();

        cout<<"Press enter key to move to next timestep"<<endl;
        cin.ignore();
        TimeStep++;
    }while(TimeStep<=50);
}

bool GameManager::BattleDone() {
    if(TimeStep==501||(TimeStep>40&&Fighters.getNumOfEarthUnits()==0)||(TimeStep>40&&Traitors.getNumOfAlienUnits()==0)) {
        win=(Fighters.getNumOfEarthUnits()>Traitors.getNumOfAlienUnits())?true:false;
        return true;
    }else{
        return false;
    }
}

void GameManager::Simulate(){

    cout<<"The program can run in two modes: interactive or silent.\n";
    cout<<"Interactive mode allows you to monitor the battle by printing:\n";
    cout<<"Alive units for earth and alien armies, units fighting at current timestep, and killed units\n";
    cout<<"Silent mode only produces the output file without printing any simulation steps\n";
    cout<<"============================================================================================\n";
    cout<<"Enter 1 for Interactive Mode or 0 for Silent Mode: ";
    int mode;
    cin>>mode;
    while (mode!=0 && mode!=1){
        cout<<"Invalid option was entered!\n";
        cout<<"Enter 1 for Interactive Mode or 0 for Silent Mode: ";
        cin>>mode;
    }
    Interactive=mode;
    switch (Interactive){
        case true:
            do {
                cout << "Current Timestep " << TimeStep << endl;
                Generator->CreateUnitsPerTimeStep();

                Fighters.PrintEarthAliveUnits();
                Savers.PrintAliveSaverUnits();
                Traitors.PrintAlienAliveUnits();


                cout<<"=========== Units Fighting at current TimeStep ===========\n";
                Attack();

                PrintKilledList();

                Fighters.SpreadInfection(this);

                cout<<"Infected ES percentage="<<Fighters.getPer_Infected()<<endl;
                cout<<"Press enter key to move to next timestep"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string line;
                getline(cin, line);
                TimeStep++;

            }while(!BattleDone());
        break;

        default:
            cout<<"Silent Mode\n";
            cout<<"Simulation Starts...\n";
            do {
                Generator->CreateUnitsPerTimeStep();
                Attack();
                TimeStep++;
            }while(!BattleDone());

            cout<<"Simulation ends, Output file is created\n";
            break;
    }
    OutputFile();
}

bool GameManager::getETAttacksAS(){return ETAttacksAS;}
void GameManager::setETAttacksAS(bool AttackAS) {ETAttacksAS=AttackAS;}

void GameManager:: OutputFile()
{
    ofstream OutputFile("OutputFile.txt");
    Unit *ptrToKilledList;

    OutputFile<<setw(3)<<"Td"<<setw(10)<<"ID"<<setw(10)<<"Tj"<<setw(10)<<"Df"<<setw(10)
              <<"Dd"<<setw(10)<<"Db"<<setw(3)<<endl;

    int InitialKilledListCount=KilledList->getCount();
    float sumDB=0;
    float sumDD=0;
    float sumDF=0;
    int ESDestructedCount=0;
    int ETDestructedCount=0;
    int EGDestructedCount=0;
    int HUDestructedCount=0;
    int ASDestructedCount=0;
    int ADDesctructedCount=0;
    int AMDestructedCount=0;
    int SUDestructedCount=0;

    while(!KilledList->isEmpty())
    {
        KilledList->dequeue(ptrToKilledList);
        OutputFile<<setw(3)<< ptrToKilledList->getTD() <<setw(10)<<ptrToKilledList->getID() <<setw(10)
                  << ptrToKilledList->getTJ()  <<setw(10)<< ptrToKilledList->getDF() <<setw(10)
                  <<  ptrToKilledList->getDD() <<setw(10)<< ptrToKilledList->getDB() <<setw(3)<<endl;
        sumDB+=ptrToKilledList->getDB();
        sumDD+=ptrToKilledList->getDD();
        sumDF+=ptrToKilledList->getDF();
        if(ptrToKilledList->getType()=="EarthTank") ETDestructedCount++;
        else if(ptrToKilledList->getType()=="EarthSoldier") ESDestructedCount++;
        else if(ptrToKilledList->getType()=="EarthGunnery") EGDestructedCount++;
        else if (ptrToKilledList->getType()=="HealUnit") HUDestructedCount++;
        else if (ptrToKilledList->getType()=="AlienMonster") AMDestructedCount++;
        else if (ptrToKilledList->getType()=="AlienDrone") ADDesctructedCount++;
        else if (ptrToKilledList->getType()=="AlienSoldier") ASDestructedCount++;
        else if(ptrToKilledList->getType()=="SaverUnit") SUDestructedCount++;
    }
    OutputFile<<endl;
    OutputFile<<setw(3)<<"Battle result: ";
    if(win){
        OutputFile<<"Win"<<endl;
    }else{
        OutputFile<<"Loss"<<endl;
    }
    OutputFile<<"The battle ended at Timestep: "<<TimeStep<<endl;
    int ESCount=ES::EScount, EGCount=EG::EGcount, ETCount=ET::ETcount, HUCount=HU::HUcount
    , ASCount=AS::AScount, AMCount=AM::AMcount, ADCount=AD::ADcount,SUCount=SU::SUcount;
    int TotalUnitsCount=ESCount+EGCount+ETCount+HUCount+ASCount+AMCount+ADCount+SUCount;
    float percentageAD=100*ADDesctructedCount/float(ADCount);
    float percentageAM=100*AMDestructedCount/float(AMCount);
    float percentageAS=100*ASDestructedCount/float(ASCount);
    float percentageEG=100*EGDestructedCount/float(EGCount);
    float percentageES=100*ESDestructedCount/float(ESCount);
    float percentageET=100*ETDestructedCount/float(ETCount);
    float percentageHU=100*HUDestructedCount/float(HUCount);
    float percentageTotal=100*InitialKilledListCount/float(TotalUnitsCount);
    float percentageSU=0;
    if(SUCount!=0)
        percentageSU=100*SUDestructedCount/float(SUCount);
    OutputFile<<setw(3)<<"For Earth Army: "<<endl;
    OutputFile<<setw(3)<<"Total Number of Each Units: "<<endl;
    OutputFile<<setw(3)<<"Earth Soldiers: "<<ESCount<<endl;
    OutputFile<<setw(3)<<"Earth Gunneries: "<<EGCount<<endl;
    OutputFile<<setw(3)<<"Earth Tanks: "<<ETCount<<endl;
    OutputFile<<setw(3)<<"Heal Units: "<<HUCount<<endl<<endl;
    OutputFile<<setw(3)<<"Percentage of destructed units relative to their count:"
              <<endl;
    OutputFile<<setw(3)<<"Earth Soldiers: "<<percentageES<<"%"<<endl;
    OutputFile<<setw(3)<<"Earth Gunneries: "<<percentageEG<<"%"<<endl;
    OutputFile<<setw(3)<<"Earth Tanks: "<<percentageET<<"%"<<endl;
    OutputFile<<setw(3)<<"Heal Units: "<<percentageHU<<"%"<<endl<<endl;
    OutputFile<<endl<<setw(3)<<"For Alien Army: "<<endl;
    OutputFile<<setw(3)<<"Total Number of Each Units: "<<endl;
    OutputFile<<setw(3)<<"Alien Soldiers: "<<ASCount<<endl;
    OutputFile<<setw(3)<<"Alien Monsters: "<<AMCount<<endl;
    OutputFile<<setw(3)<<"Alien Drones: "<<ADCount<<endl<<endl;
    OutputFile<<setw(3)<<"Percentage of destructed units relative to their count:"
              <<endl;
    OutputFile<<setw(3)<<"Alien Soldiers: "<<percentageAS<<"%"<<endl;
    OutputFile<<setw(3)<<"Alien Monsters: "<<percentageAM<<"%"<<endl;
    OutputFile<<setw(3)<<"Alien Drones: "<<percentageAD<<"%"<<endl<<endl;

    OutputFile<<setw(3)<<"For Ally Army: "<<endl;
    OutputFile<<setw(3)<<"Total Number of Each Units: "<<endl;
    OutputFile<<setw(3)<<"Saver Units: "<<SUCount<<endl;
    OutputFile<<setw(3)<<"Percentage of destructed units relative to their count:"
              <<endl;
    OutputFile<<setw(3)<<"Saver Units: "<<percentageSU<<"%"<<endl;
    float percentage_inf=float(TotalInfectedSoldiers)/float(ESCount)*100.0;
    OutputFile<<setw(3)<<"Percentage of infected soldier: "<<percentage_inf<<"%"
              <<endl;

    OutputFile<<endl;

    OutputFile<<setw(3)<<"Total Percentage of destructed units for the 3 armies: "<<percentageTotal<<"%"<<endl;


    OutputFile<<setw(3)<<"Average of First Attack Delay (Df): "<<sumDF/InitialKilledListCount<<endl;
    OutputFile<<setw(3)<<"Average of Destruction Delay (Dd): "<<sumDD/InitialKilledListCount<<endl;
    OutputFile<<setw(3)<<"Average of Battle Time (Db): "<<sumDB/InitialKilledListCount<<endl;
    OutputFile<<endl;

    OutputFile<<setw(3)<<"Df/Db: "<<((sumDF/InitialKilledListCount)/(sumDB/InitialKilledListCount))*100<<"%"<<endl;
    OutputFile<<setw(3)<<"Dd/Db: "<<((sumDD/InitialKilledListCount)/(sumDB/InitialKilledListCount))*100<<"%"<<endl;
    OutputFile.close();

}

int GameManager::getThresholdAllyarmy() const {
    return ThresholdAllyarmy;
}

void GameManager::setThresholdAllyarmy(int thresholdAllyarmy) {
    ThresholdAllyarmy = thresholdAllyarmy;
}

int GameManager::RandomAB()
{
    return Generator->randomAB();
}

bool GameManager::isCallSavers() const {
    return CallSavers;
}

bool GameManager::isSaversWithdraw() const {
    return SaversWithdraw;
}

void GameManager::IncrementTotalInfectedES() {TotalInfectedSoldiers++;}