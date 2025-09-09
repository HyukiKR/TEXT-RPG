#pragma once
#ifndef DRAGON_H
#define DRAGON_H

#include "Monster.h"

class Dragon : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Dragon(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	std::string getIntro() const override;
	std::string getDeathLine() const override;
};

#endif