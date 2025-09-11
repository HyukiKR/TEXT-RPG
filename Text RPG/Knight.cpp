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

void Knight::attackMassage() // 기사의 공격
{
	int category = randNum(0, 1);

	if (category == 0)
	{
		cout << "검을 휘둘러 베어버리자! " << endl;
	}
	else
	{
		cout << "검을 빠르게 내밀어 찔러버리자! " << endl;
	}
}
