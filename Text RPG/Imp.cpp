#include <iostream>
#include "Imp.h"

int Imp::randNum(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

Imp::Imp(int level) {
    name = "Imp";
    health = 25;
    maxHealth = health;
    attack = 5;
}

string Imp::getName() {
    return name;
}
int Imp::getHealth() {
    return health;
}
int Imp::getAttack() {
    return attack;
}

string Imp::getIntro() {
    return "너도 내 보물 훔지러왔심?";
}

string Imp::getDeathLine() {
    return "죽어서 저주할거임 흑흑";
}

int Imp::getMaxHealth() {
    return maxHealth;
}

void Imp::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}
