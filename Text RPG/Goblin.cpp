#include <iostream>
#include "Goblin.h"

using namespace std;

Goblin::Goblin(int level) {
	name = "Goblin";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string Goblin::getName() {
	return name;
}

int Goblin::getHealth() {
	return health;
}

int Goblin::getAttack() {
	return attack;
}

int Goblin::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

void Goblin::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}