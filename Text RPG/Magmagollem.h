#pragma once
#ifndef Magmagollem_H
#define Magmagollem_H

#include "Monster.h"

class Magmagollem : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	Magmagollem(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	std::string getIntro() const override;
	std::string getDeathLine() const override;
};
#endif 
