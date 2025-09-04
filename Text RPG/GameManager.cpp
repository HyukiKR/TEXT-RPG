#include "GameManager.h"
#include <iostream>
#include <random>

// 전투 화면에 출력되는 선택지
void displayBattleChoice()
{
	cout <<  endl <<  "---------------------------" << endl;
	cout << "전투 시스템" << endl;
	cout << "1. 공격" << endl;
	cout << "2. 게임 종료" << endl;
	cout << "---------------------------" << endl << endl;
	cout << "선택: ";
}

Monster* GameManager::generateMonster(int level)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, 3);

	int ran = dist(gen);

	switch (ran)
	{
	case 0:
		return new Goblin(level);
	case 1:
		return new Troll(level);
	case 2:
		return new Orc(level);
	case 3:
		return new Slime(level);
	default:
		return nullptr;
	}
}

void GameManager::battle(Character* Player)
{
	int tempHealth;
	Monster* monster = generateMonster(Player->getLevel());
	cout << "몬스터 " << monster->getName() << " 등장! 체력: " << monster->getHealth() << ", 공격력: " << monster->getAttack() << endl;
	while (true)
	{
		displayBattleChoice();
		int choice;
		cin >> choice;
		if (cin.fail()) {
			cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		switch (choice)
		{
		case 1:
			//플레이어 공격
			cout << Player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! ";
			monster->takeDamage(Player->getAttack());
			if (monster->getHealth() <= 0)
			{
				cout << monster->getName() << "처치!" << endl;
				delete monster;
				return;
			}
			else
			{
				cout << monster->getName() << " 체력: " << monster->getHealth() << endl;
			}
			//몬스터 공격
			cout << monster->getName() << "이(가) " << Player->getName() << "을(를) 공격합니다! ";
			tempHealth = Player->getHealth();
			Player->takeDamage(monster->getAttack());
			if (Player->getHealth() <= 0)
			{
				cout << Player->getName() << "체력: " << tempHealth << " -> " << Player->getHealth() << endl;
				cout << Player->getName() << "가 사망했습니다. 게임 오버!" << endl;
				exit(0);
			}
			else
			{
				cout << Player->getName() << " 체력: " << Player->getHealth() << endl;
			}
			break;
		case 2:
			cout << "게임을 종료합니다." << endl;
			exit(0);
			break;
		}
	}
}

void GameManager::displayInventory(Character* Player)
{
	//인벤토리 디스플레이 시스템
}