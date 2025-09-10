#include <iostream>
#include "BossMonster.h"
using namespace std;

BossMonster::BossMonster(int level) {
	name = "BossMonster";
	intro = "하찮은 인간이 감히 여기까지 오는구나";
	deathline = "내가 인간따위에게 지다니..";
	health = level * randNum(20, 30);
	attack = level * randNum(5, 10);
}

string BossMonster::getName() {
	return name;
}

int BossMonster ::getHealth() {
	return health;
}

int BossMonster ::getAttack() {
	return attack;
}

int BossMonster::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string BossMonster::getIntro() {
	return intro;
}
string BossMonster::getDeathLine() {
	return deathline;
}


void BossMonster::takeDamage(int damage) {
	health -= damage;
	if (health < 0) health = 0;
}
