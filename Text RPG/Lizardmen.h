#pragma once

#ifndef lizardmen_H
#define lizardmen_H

#include "Monster.h"

class lizardmen : public Monster {
private:
	string name;
	int health;
	int attack;

public:
	lizardmen(int level);
	string getName();
	int getHealth();
	int getAttack();
	void takeDamage(int damage);
	int randNum(int min, int max);

	std::string getIntro() const override;
	std::string getDeathLine() const override;
};
#endif 
