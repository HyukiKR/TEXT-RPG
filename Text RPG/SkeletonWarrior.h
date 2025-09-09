#pragma once

#ifndef SkeletonWarrior_H
#define SkeletonWarrior_H

#include "Monster.h"

class SkeletonWarrior : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	SkeletonWarrior(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	std::string getIntro() const override;
	std::string getDeathLine() const override;
};
#endif 
