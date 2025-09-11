#pragma once
#ifndef Zombie_H
#define Zombie_H

#include "Monster.h"

class Zombie : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	Zombie(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	string getIntro();
	string getDeathLine();
};
#endif 