#include <iostream>
#include "Magmagollem.h"

using namespace std;

Magmagollem::Magmagollem(int level) {
	name = "Magmagollem";
	health = level * randNum(20, 30) * 1.4;
	attack = level * randNum(5, 10) * 1.4;
}

string Magmagollem::getName() {
	return name;
}

int Magmagollem::getHealth() {
	return health;
}

int Magmagollem::getAttack() {
	return attack;
}

int Magmagollem::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string Magmagollem::getIntro() const {
	return "...."
}
string Magmagollem::getAttackDeathLine() const {
	return "(바위가 부셔시며 핵만 남았다.)"
}

void  Magmagollem::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}