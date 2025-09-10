#include <iostream>
#include "Alchemist.h"
using namespace std;

Alchemist::Alchemist(string t_name) : Character(t_name)
{
	maxHealth = 150;
	health = maxHealth;
	attack = 13;
	job_name = "연금술사";
}

void Alchemist::passiveSkill() // 매 턴 공격력이 (-1 ~ +2)로 조정
{
	int effect = randNum(-1, 2);

	attack += effect;

	if (effect == 0)
	{
		cout << name << "은(는) 약물을 복용했지만 아무런 효과가 없었다!" << endl;
	}
	else if (effect < 0)
	{
		cout << name << "은(는) 약물의 부작용으로 공격력이 " << effect << " 만큼 감소했다!" << endl;
	}
	else
	{
		cout << name << "은(는) 약물의 효과로 공격력이 " << effect << " 만큼 증가했다!" << endl;
	}

}
