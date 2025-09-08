#include <iostream>
#include "SkeletonWarrior.h"

using namespace std;

SkeletonWarrior::SkeletonWarrior(int level) {
	name = "SkeletonWarrior";
	health = level * randNum(20, 30) * 1.2;
	attack = level * randNum(5, 10) * 1.2;
}

string SkeletonWarrior::getName() {
	return name;
}

int SkeletonWarrior::getHealth() {
	return health;
}

int SkeletonWarrior::getAttack() {
	return attack;
}

int SkeletonWarrior::randNum(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

string SkeletonWarrior::getIntro() const {
	return ".....(검을 들고 다가온다)"
}
string SkeletonWarrior::getAttackDeathLine() const {
	return "(뼈가 흐트러지며 주저앉았다)"
}

void SkeletonWarrior::takeDamage(int damage) {
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}

