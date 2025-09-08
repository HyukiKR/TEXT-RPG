#pragma once
#ifndef Wolf_H
#define Wolf_H

#include "Monster.h"

class Wolf : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Wolf(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};

#endif 