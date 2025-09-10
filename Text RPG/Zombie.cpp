#include <iostream>
#include "Zombie.h"

using namespace std;

Zombie::Zombie(int level) {
	name = "Zombie";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string Zombie::getName() {
	return name;
}

int Zombie::getHealth() {
	return health;
}

int Zombie::getAttack() {
	return attack;
}

int Zombie::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string Zombie::getIntro() {
	return "으..어어.....";
}
string Zombie::getDeathLine() {
	return "으어...(행동이 멈췄다)";
}

void Zombie::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}
