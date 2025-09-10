#pragma once
#ifndef Wolf_H
#define Wolf_H

#include "Monster.h"
#include <string>

class Wolf : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	Wolf(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
	string getIntro();
	string getDeathLine();
};
#endif 