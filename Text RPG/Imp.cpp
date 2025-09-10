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
    attack = 5;
}

string Imp::getName() const {
    return name;
}
int Imp::getHealth() const {
    return health;
}
int Imp::getAttack() const {
    return attack;
}

string Imp::getIntro() const {
    return "너도 내 보물 훔지러왔심?";
}

string Imp::getDeathLine() const {
    return "죽어서 저주할거임 흑흑";
}

void Imp::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}
