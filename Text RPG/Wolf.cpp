#include <iostream>
#include "Wolf.h"

using namespace std;

Wolf::Wolf(int level) {
	name = "Wolf";
	intro = "嬴辦辦辦辦~";
	deathline = "郭釧.. 郭濘..";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string Wolf::getName() {
	return name;
}

int Wolf::getHealth() {
	return health;
}

int Wolf::getAttack() {
	return attack;
}

int Wolf::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string Wolf::getIntro() {
	return intro;
}
string Wolf::getDeathLine(){
	return deathline;
}

void Wolf::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}
