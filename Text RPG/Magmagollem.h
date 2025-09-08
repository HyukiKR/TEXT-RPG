#pragma once
#ifndef magmagollem_H
#define magmagollem_H

#include "magmagollem.h"

class magmagollem : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	magmagollem(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};
#endif 
