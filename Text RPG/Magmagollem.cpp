#include <iostream>
#include "magmagollem.h"

using namespace std;

magmagollem::magmagollem(int level) {
	name = "magmagollem";
	health = level * randNum(20, 30) * 1.4;
	attack = level * randNum(5, 10) * 1.4;
}

string magmagollem::getName() {
	return name;
}

int magmagollem::getHealth() {
	return health;
}

int magmagollem::getAttack() {
	return attack;
}

int magmagollem::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string magmagollem::getIntro() const {
	return "...."
}
string magmagollem::getAttackDeathLine() const {
	return "(바위가 부셔시며 핵만 남았다.)"
}

void  magmagollem::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}
