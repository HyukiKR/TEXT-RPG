#include <iostream>
#include "Orc.h"

using namespace std;

Orc::Orc(int level) {
	name = "Orc";
	intro = "무기를 들어라, 결투다";
	deathline = "크으윽. 명예로운 죽음이다";
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

string Orc::getIntro() {
	return intro;
}
string Orc::getDeathLine() {
	return deathline;
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