#include <iostream>
#include "Slime.h"

using namespace std;

Slime::Slime(int level) {
	name = "Slime";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string Slime::getName() {
	return name;
}

int Slime::getHealth() {
	return health;
}

int Slime::getAttack() {
	return attack;
}

int Slime::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

void Slime::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}