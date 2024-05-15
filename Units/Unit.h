//
// Created by ahmed on 06/03/2024.
//
#include <string>
#include <iostream>

using namespace std;
#pragma once
class GameManager;
//class ES;
class Unit {

protected:
    int ID;
    std::string Type;
    int TJ;
    int Health;
    int Power;
    int AttackCapacity;
    int TA=0;
    int TD;
    int DF;
    int DD;
    int DB;
    float UAP;

public:

    int getID() const{return ID;}
    std::string getType() const {return Type;}
    int getTJ() const {return TJ;}
    int getHealth() const {return Health;}
    int getPower() const {return Power;}
    int getAttackCapacity() const {return AttackCapacity;}
    int getTA() const {return TA;}
    int getTD() const {return TD;}
    int getDF() const {return DF;}
    int getDD() const {return DD;}
    int getDB() const {return DB;}
    float getUAP() const {return UAP;}

    void setID(int ID){this->ID=ID;}
    void setType(std::string Type){this->Type=Type;}
    void setHealth(int Health){this->Health=Health;}
    void setTJ(int TJ){this->TJ=TJ;}
    void setPower(int Power){this->Power=Power;}
    void setAttackCapacity(int AttackCapacity){this->AttackCapacity=AttackCapacity;}
    void setTA(int TA){this->TA=TA;}
    void setTD(int TD){this->TD=TD;}
    void setDF(int DF){this->DF=DF;}
    void setDD(int DD){this->DD=DD;}
    void setDB(int DB){this->DB=DB;}
    void setUAP(float UAP){this->UAP=UAP;}

    virtual void Attack(GameManager* gameptr)=0;

};

static ostream& operator<<(ostream& Output, const Unit& unit)
{

    Output<<unit.getID()<<" ";
    return Output;
};