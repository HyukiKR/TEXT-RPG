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
    int attack;

public:
    DemonLord(int level);
    string getName() const;
    int getHealth() const;
    int getAttack() const;
    void takeDamage(int damage);
    int randNum(int min, int max);

    string getIntro() const;
    string getDeathLine() const;
};

#endif
