#pragma once
#ifndef DEMONLORD_H
#define DEMONLORD_H

#include "Monster.h"

class DemonLord : public Monster {
private:
    string name;
    string intro;
    string deathline;
    int health;
    int maxHealth;
    int attack;

public:
    DemonLord(int level);
    string getName();
    int getHealth();
    int getAttack();
    int getMaxHealth();
    void takeDamage(int damage);
    int randNum(int min, int max);

    string getIntro();
    string getDeathLine();
};

#endif
