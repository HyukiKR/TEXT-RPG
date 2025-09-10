#include <iostream>
#include "Orc.h"

using namespace std;

Orc::Orc(int level) {
	name = "Orc";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string Orc::getName() {
	return name;
}

int Orc::getHealth() {
	return health;
}

int Orc::getAttack() {
	return attack;
}

int Orc::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

void Orc::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}