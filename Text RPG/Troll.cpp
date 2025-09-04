#include <iostream>
#include "Troll.h"

using namespace std;

Troll::Troll(int level) {
	name = "Troll";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string Troll::getName() {
	return name;
}

int Troll::getHealth() {
	return health;
}

int Troll::getAttack() {
	return attack;
}

int Troll::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

void Troll::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}