#include <iostream>
#include "Pirate.h"
using namespace std;

Pirate::Pirate(string t_name) : Character(t_name)
{
	maxHealth = 220;
	health = maxHealth;
	attack = 10;
	job_name = "해적";
}

void Pirate::passiveSkill() // 매턴 1~10 골드 추가획득
{
	int ran = randNum(1, 10);
	int steal = randNum(0, 2);

	gold += ran;
	switch (steal)
	{
	case 0:
		cout << name << "은(는) " << ran << " 골드를 소매치기했다!" << endl;
		break;

	case 1:
		cout << name << "은(는) " << ran << " 골드를 뺏어왔다!" << endl;
		break;

	case2:
		cout << name << "은(는) " << ran << " 골드를 슬쩍했다!" << endl;
		break;
	}
}