#include "GameManager.h"
#include <iostream>

using namespace std;

Character* Character::instance = nullptr;


int main() 
{
	GameManager gameManager;
	Monster* monster = nullptr;


	cout << "캐릭터 이름을 입력하세요: ";
	string name;
	cin >> name;
	Character* player = Character::getInstance(name);
	cout << "캐릭터 " << name << " 생성 완료! 레벨: " << player->getLevel() << ", 체력: " <<
		player->getHealth() << ", 공격력: " << player->getAttack() << endl << endl;


	gameManager.battle(player);

	return 0;
}