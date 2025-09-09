#include <iostream>
#include "Knight.h"
using namespace std;

Knight::Knight(string t_name) : Character(t_name)
{
	maxHealth = 200;
	health = maxHealth;
	attack = 15;
	job_name = "기사";
}

void Knight::passiveSkill() // 매 턴 체력을 최대체력의 3%정도 회복
{
	int heal = maxHealth / 30;

	health += heal;
	cout << name << "은(는) 체력을 " << heal << " 회복했다!" << endl;
}
