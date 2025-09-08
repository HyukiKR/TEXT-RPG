#pragma once
#ifndef DEMONLORD_H
#define DEMONLORD_H

#include "Monster.h"

using namespace std;

class DemonLord : public Monster {
private:
    string name;
    int health;
    int attack;

public:
    DemonLord(int level);
    string getName() ;
    int getHealth() ;
    int getAttack();
    void takeDamage(int damage);
    int randNum(int min, int max);
};

#endif