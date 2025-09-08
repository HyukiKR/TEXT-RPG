#pragma once
#ifndef DEMONLORD_H
#define DEMONLORD_H

#include "Monster.h"

class DemonLord : public Monster {
private:
    string name;
    int health;
    int attack;

public:
    DemonLord(int level);
    string getName() const;
    int getHealth() const;
    int getAttack() const;
    void takeDamage(int damage);
    int randNum(int min, int max);

    std::string getIntro() const override;
    std::string getDeathLine() const override;
};

#endif