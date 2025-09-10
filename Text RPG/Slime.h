#pragma once
#ifndef SLIME_H
#define SLIME_H

#include "Monster.h"

class Slime : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Slime(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};

#endif // !SLIME_H