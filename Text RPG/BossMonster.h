#pragma once
#include "Monster.h"

#ifndef BOSSMONSTER_H
#define BOSSMONSTER_H


class  BossMonster : public Monster {
private:
	string name;
	string intro;
	string deathline;
	int health;
	int attack;

public:
	BossMonster(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	string getIntro() ;
	string getDeathLine() ;
};

#endif

