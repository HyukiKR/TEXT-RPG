#pragma once

#ifndef Lizardmen_H
#define Lizardmen_H

#include "Monster.h"

class Lizardmen : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	Lizardmen(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	string getIntro();
	string getDeathLine();
};
#endif 
