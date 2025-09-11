#pragma once
#ifndef Imp_H
#define Imp_H

#include "Monster.h"

class Imp : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int maxHealth;
	int attack;

public:
	Imp(int level);
	string getName();
	int getHealth();
	int getAttack();
	int getMaxHealth();
	void takeDamage(int damage);
	int randNum(int min, int max);

	std::string getIntro();
	std::string getDeathLine();
};

#endif
