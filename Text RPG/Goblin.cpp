#include <iostream>
#include "Goblin.h"

using namespace std;

Goblin::Goblin(int level) {
	name = "Goblin";
	intro = "Å±Å± µ·³»³ö¶ó ÀÎ°£";
	deathline = "³¢ÀÍ.. ³ª Á×´Â´Ù";
	health = level * randNum(20, 30);
	maxHealth = health;
	attack = level * randNum(5, 10);
}

string Goblin::getName() {
	return name;
}

int Goblin::getMaxHealth() {
	return maxHealth;
}

int Goblin::getHealth() {
	return health;
}

int Goblin::getAttack() {
	return attack;
}

string Goblin::getIntro() {
	return intro;
}
string Goblin::getDeathLine() {
	return deathline;
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