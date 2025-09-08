#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <random>

using namespace std;

class Monster {
public:
	virtual ~Monster() = default;

	virtual string getName() = 0;
	virtual int getHealth() = 0;
	virtual int getAttack() = 0;
	virtual void takeDamage(int damage) = 0;
};

#endif // !MONSTER_H