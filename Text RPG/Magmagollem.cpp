#include <iostream>
#include "Magmagollem.h"
#include <Random>

using namespace std;

Magmagollem::Magmagollem(int level) {
	name = "Magmagollem";
	intro = "Äô.. Äô..";
	deathline = "(¹ÙÀ§°¡ ºÎ¼Å½Ã¸ç ÇÙ¸¸ ³²¾Ò´Ù.)";
	health = level * randNum(20, 30);
	maxHealth = health;
	attack = level * randNum(5, 10);

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

int Magmagollem::getMaxHealth() {
	return maxHealth;
}

string Magmagollem::getIntro() {
	return intro;
}
string Magmagollem::getDeathLine() {
	return deathline;
}

void Magmagollem::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}
