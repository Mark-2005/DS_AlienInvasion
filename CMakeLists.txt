cmake_minimum_required(VERSION 3.26)
project(DS_AlienInvasion)

set(CMAKE_CXX_STANDARD 17)

add_executable(DS_AlienInvasion main.cpp
        Units/ET.h
        Units/ET.cpp
        Units/EG.h
        Units/EG.cpp
        Units/AM.h
        Units/AM.cpp
        Units/AD.h
        Units/AD.cpp
        Armies/EarthArmy.h
        Armies/EarthArmy.cpp
        Armies/AlienArmy.h
        Armies/AlienArmy.cpp
        DataStructures/Queue.h
        DataStructures/Stack.h
        DataStructures/StackADT.h
        DataStructures/QueueADT.h
        DataStructures/priNode.h
        DataStructures/DEqueue.h
        DataStructures/PriorityQueue.h
        Units/ES.h
        Units/ES.cpp
        Units/AS.h
        Units/AS.cpp
        DataStructures/Monsters_arr.h
        DataStructures/Monsters_arr.cpp
        GameManager/GameManager.h
        GameManager/GameManager.cpp
        randGen/randGen.h
        randGen/randGen.cpp
        Units/HU.cpp
        Units/HU.h
        Units/SU.h
        Units/SU.cpp
        Armies/AllyArmy.h
        Armies/AllyArmy.cpp
        Units/Unit.h
)
