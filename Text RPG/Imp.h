#pragma once
#ifndef Imp_H
#define Imp_H

#include "Monster.h"

class Imp : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Imp(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};

#endif 