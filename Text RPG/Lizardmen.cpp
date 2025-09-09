#include <iostream>
#include "lizardmen.h"

using namespace std;

lizardmen::lizardmen(int level) {
	name = "lizardmen";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string lizardmen::getName() {
	return name;
}

int lizardmen::getHealth() {
	return health;
}

int lizardmen::getAttack() {
	return attack;
}

int lizardmen::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string lizardmen::getIntro() const {
	return "우리영역에서 나가라 인간..";
}
string lizardmen::getDeathLine() const {
	return "(내 동료들이 나의 복수를 해줄 것이다. )";
}

void  lizardmen::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}
