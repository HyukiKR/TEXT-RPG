#pragma once
#ifndef Magmagollem_H
#define Magmagollem_H

#include "Monster.h"

class Magmagollem : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int maxHealth;
	int attack;

public:
	Magmagollem(int level);
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
