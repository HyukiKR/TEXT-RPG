#include <iostream>
#include "Lizardmen.h"

using namespace std;

Lizardmen::Lizardmen(int level) {
	name = "Lizardmen";
	intro = "우리영역에서 나가라 인간..";
	deathline = "(내 동료들이 나의 복수를 해줄 것이다. )";
	health = level * randNum(20, 30);
	maxHealth = health;
	attack = level * randNum(5, 10);
}

string Lizardmen::getName() {
	return name;
}

int Lizardmen::getHealth() {
	return health;
}

int Lizardmen::getAttack() {
	return attack;
}

int Lizardmen::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

int Lizardmen::getMaxHealth() {
	return maxHealth;
}

string Lizardmen::getIntro() {
	return intro;
}
string Lizardmen::getDeathLine() {
	return deathline;
}

void  Lizardmen::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}
