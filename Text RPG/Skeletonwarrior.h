#pragma once

#ifndef SkeletonWarrior_H
#define SkeletonWarrior_H

#include "Monster.h"

class SkeletonWarrior : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	SkeletonWarrior(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	string getIntro();
	string getDeathLine();
};
#endif 
