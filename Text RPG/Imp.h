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
	int attack;

public:
	Imp(int level);
	string getName() const;
	int getHealth() const;
	int getAttack() const;
	void takeDamage(int damage);
	int randNum(int min, int max);

	std::string getIntro() const;
	std::string getDeathLine() const;
};

#endif
