#pragma once
#ifndef ORC_H
#define ORC_H

#include "Monster.h"

class Orc : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Orc(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};

#endif // !ORC_H