#pragma once
#ifndef Magmagollem_H
#define Magmagollem_H

#include "Magmagollem.h"

class Magmagollem : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Magmagollem(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};
#endif 
