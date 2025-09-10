#pragma once
#ifndef TROLL_H
#define TROLL_H

#include "Monster.h"

class Troll : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	Troll(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);
	string getIntro();
	string getDeathLine();
};

#endif // !TROLL_H