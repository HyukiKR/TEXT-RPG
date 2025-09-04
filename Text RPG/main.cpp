#include "GameManager.h"
#include <iostream>

using namespace std;

Character* Character::instance = nullptr;


int main() 
{
	GameManager gameManager;
	Monster* monster = nullptr;


	cout << "ĳ���� �̸��� �Է��ϼ���: ";
	string name;
	cin >> name;
	Character* player = Character::getInstance(name);
	cout << "ĳ���� " << name << " ���� �Ϸ�! ����: " << player->getLevel() << ", ü��: " <<
		player->getHealth() << ", ���ݷ�: " << player->getAttack() << endl << endl;


	gameManager.battle(player);

	return 0;
}