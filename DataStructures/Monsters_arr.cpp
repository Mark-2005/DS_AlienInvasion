//
// Created by Mark on 4/3/2024.
//

#include "Monsters_arr.h"
#include <iostream>
namespace std {
    Monsters_arr::Monsters_arr()
    {
        count=0;
        for(int i=0;i<100;i++)
        {
            arr[i]=NULL;
        }
    }

    bool Monsters_arr::RemoveAnyMonster(AM*& monster)
    {
        if(count==0)
            return false;
        else
        {
            int n = rand() % count;
            monster = arr[n];
            arr[n]=arr[count-1];
            count --;
            return true;
        }
    }

    bool Monsters_arr::AddMonster(AM* &monster)
    {
        if(count==100)
            return false;
        else
        {
            arr[count]=monster;
            count++;
            return true;
        }
    }

    bool Monsters_arr::isEmpty() const {return count==0;}

    bool Monsters_arr::RemoveMonster(AM* &monster)
    {
        if(count==0)
            return false;
        else
        {
            for(int i=0;i<count;i++)
            {
                if(arr[i]==monster)
                {
                    arr[i]=arr[count-1];
                    count--;
                    return true;
                }
            }
        }
        return false;

    }
    void Monsters_arr::Printarr() const
    {
        if(!isEmpty()) cout<<"[ "; else return;
        for(int i=0;i<count;i++)
        {
            cout<<*arr[i];
        }
        cout<<"]"<<endl;
        return;
    }

    Monsters_arr::~Monsters_arr() {
        for(int i=0;i<count;i++){
            arr[i]=nullptr;
        }
    }

    int Monsters_arr::getCount() const {return count;}
}