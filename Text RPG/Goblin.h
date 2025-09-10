#pragma once
#ifndef GOBLIN_H
#define GOBLIN_H

#include "Monster.h"

class Goblin : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	Goblin(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	string getIntro() ;
	string getDeathLine() ;
};
#endif // !GOBLIN_H
