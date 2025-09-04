#pragma once
#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"

class Goblin : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Goblin(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};
#endif // !GOBLIN_H
