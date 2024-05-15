#include <iostream>
using namespace std;

#include "Armies/EarthArmy.h"
#include "Armies/AlienArmy.h"

#include "GameManager/GameManager.h"

int main() {
    GameManager Game;
//    Game.Phase1TestCode();
    Game.Simulate();
    cout<<"Done"<<endl;

//    ES* EarthGondy=new ES(1,20,50,1);
//    Game.MoveToSoldiersUML(EarthGondy,100-EarthGondy->getHealth());
//    HU* Medic=new HU(1,100,100,1);
//    Medic->Attack(&Game);
   // cout<<"new health of soldier"<<EarthGondy->getHealth()<<endl;
    return 0;
}