#pragma once

#ifndef SLIME_H
#define SLIME_H

#include "Monster.h"

class Slime : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int maxHealth;
	int attack;

public:
	Slime(int level);
	string getName();
	string getIntro();
	string getDeathLine();
	int getHealth();
	int getMaxHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);


};

#endif // !SLIME_H