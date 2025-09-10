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
		cout << name << "은(는) 공격을하면서 " << ran << " 골드를 소매치기했다!" << endl;
		break;

	case 1:
		cout << name << "은(는) 칼들고 협박하여 " << ran << " 골드를 뺏어왔다!" << endl;
		break;

	case 2:
		cout << name << "은(는) 화약으로 시선을 끌고 " << ran << " 골드를 슬쩍했다!" << endl;
		break;
	}
}

void Pirate::attackMassage() // 해적의 공격
{
	int category = randNum(0, 1);

	if (category == 0)
	{
		cout << "소형 폭탄을 던지자! " << endl;
	}
	else
	{
		cout << "권총으로 버르장머리를 선물해주자!  " << endl;
	}
}