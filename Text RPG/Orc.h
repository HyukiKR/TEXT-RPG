#pragma once
#ifndef ORC_H
#define ORC_H

#include "Monster.h"

class Orc : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int maxHealth;
	int attack;

public:
	Orc(int level);
	string getName();
	int getHealth();
	int getAttack();
	int getMaxHealth();
	void takeDamage(int damage);
	int randNum(int min, int max);
	string getIntro();
	string getDeathLine();
};

#endif // !ORC_H