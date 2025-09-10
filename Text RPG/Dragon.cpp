#include <iostream>
#include "Dragon.h"
using namespace std;

Dragon::Dragon(int level) {
	name = "Dragon";
	intro = "하찮은 인간이 감히 여기까지 오는구나";
	deathline = "내가 인간따위에게 지다니..";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string Dragon::getName() {
	return name;
}

int Dragon::getHealth() {
	return health;
}

int Dragon::getAttack() {
	return attack;
}

int Dragon::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string Dragon::getIntro() const {
	return intro;
}
string Dragon::getDeathLine() const {
	return deathline;
}


void Dragon::takeDamage(int damage) {
	health -= damage;
	if (health < 0) health = 0;
}
