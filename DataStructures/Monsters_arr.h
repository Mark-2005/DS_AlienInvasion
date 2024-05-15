//
// Created by Mark on 4/3/2024.
//

#pragma once
#include "../Units/AM.h"
#include <iostream>
namespace std {

    class Monsters_arr {
    private:
        AM *arr[1000];
        int count;
    public:
        Monsters_arr();
        bool AddMonster(AM*& monster);
        bool RemoveMonster(AM*& monster);
        bool RemoveAnyMonster(AM*& monster);
        bool isEmpty() const;
        void Printarr() const;
        int getCount() const;
        ~Monsters_arr() ;
    };

}

 //DS_ALIENINVASION_MONSTERS_ARR_H