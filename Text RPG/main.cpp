#include "GameManager.h"
#include <iostream>
#include "Character.h"
#include "Knight.h"
#include "Alchemist.h"
#include "Pirate.h"
#include "Farmer.h"
#include "Intro.h"

using namespace std;

Character* Character::instance = nullptr;


int main() 
{
	GameManager gameManager;
	Monster* monster = nullptr;

    Intro().displayIntro(); //인트로 화면 출력

	cout << "캐릭터 이름을 입력하세요: ";
	string name;
	cin >> name;

	int job_choice = 0;
	for (;;)
	{
		cout << "원하는 직업을 선택해주세요." << endl << "1. 기사  2. 연금술사  3. 해적  4. 농부" << endl;
		cin >> job_choice;
		if (job_choice > 0 && job_choice < 5)
		{
			break;
		}
		else
		{
			cout << "잘못된 입력입니다" << endl;
		}
	}



	Character* player = Character::getInstance(name, job_choice);
	cout << player->getJobName() <<" " << name << " 생성 완료! 레벨: " << player->getLevel() << ", 체력: " <<
		player->getHealth() << ", 공격력: " << player->getAttack() << endl << endl;


	gameManager.battle(player);

	//푸시 테스트 용 주석

	return 0;
}