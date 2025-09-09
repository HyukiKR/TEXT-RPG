#include <iostream>
#include "DemonLord.h"


int DemonLord::randNum(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

DemonLord::DemonLord(int level) {
    name = "DemonLord";
    health = level * randNum(20, 30) * 2;
    attack = level * randNum(5, 10) * 2;
}

string DemonLord::getName() const {
    return name; 
}
int DemonLord::getHealth() const { 
    return health; 
}
int DemonLord::getAttack() const { 
    return attack; 
}

string DemonLord::getIntro() const {
    return "내 애완동물을 이기고오다니 쓸만한 녀석이구나";
}

string DemonLord::getDeathLine() const {
    return "말도 안 돼... 내가... 지다니...하지만 끝이 아니다! ";
}

void DemonLord::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}