#pragma once

#ifndef Zombie_H
#define Zombie_H

#include "Zombie.h"

class Zombie : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Zombie(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
};
#endif 
