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
	int maxHealth;
	int attack;

public:
	Dragon(int level);
	string getName();
	int getHealth();
	int getAttack();
	int getMaxHealth();
	void takeDamage(int damage);
	int randNum(int min, int max);

	string getIntro();
	string getDeathLine();
};

#endif
