#pragma once
#ifndef DRAGON_H
#define DRAGON_H

#include "Monster.h"

class Dragon : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	Dragon(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	string getIntro() const;
	string getDeathLine() const;
};

#endif
