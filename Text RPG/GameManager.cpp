#include "GameManager.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// 전투 화면에 출력되는 디스플레이
void displayBattleChoice()
{
	cout << endl << "---------------------------" << endl;
	cout << "전투 시스템" << endl;
	cout << "1. 공격" << endl;
	cout << "2. 게임 종료" << endl;
	cout << "---------------------------" << endl << endl;
	cout << "선택: ";
}

Monster* GameManager::generateMonster(int level)
{
	int ran = randNum(0, 3);

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

// 여러 몬스터 생성 메소드
vector<Monster*> GameManager::generateMultipleMonsters(int playerLevel)
{
	vector<Monster*> monsters;
	int monsterCount = randNum(2, 4);  // 2~4마리 생성

	cout << "여러 몬스터가 나타났다! (총 " << monsterCount << "마리)" << endl;

	for (int i = 0; i < monsterCount; i++)
	{
		// 플레이어 레벨 -1 ~ 플레이어 레벨 범위의 몬스터 생성
		int monsterLevel = max(1, playerLevel - randNum(0, 1));
		Monster* monster = generateMonster(monsterLevel);
		monsters.push_back(monster);
		cout << (i + 1) << ". " << monster->getName()
			<< " (체력: " << monster->getHealth()
			<< ", 공격력: " << monster->getAttack() << ")" << endl;
	}

	return monsters;
}

// 다중 몬스터 전투
void GameManager::multiBattle(Character* Player, vector<Monster*>& monsters)
{
	int totalExp = 0;
	int defeatedCount = 0;

	cout << endl << "=== 다중 몬스터 전투 시작! ===" << endl;

	while (!monsters.empty() && Player->getHealth() > 0)
	{
		// 현재 남은 몬스터 표시
		cout << endl << "--- 남은 몬스터 ---" << endl;
		for (int i = 0; i < monsters.size(); i++)
		{
			cout << (i + 1) << ". " << monsters[i]->getName()
				<< " (체력: " << monsters[i]->getHealth() << ")" << endl;
		}

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
		{
			// 공격할 몬스터 선택
			cout << "공격할 몬스터 번호를 선택하세요: ";
			int targetIndex;
			cin >> targetIndex;

			if (targetIndex < 1 || targetIndex > monsters.size())
			{
				cout << "잘못된 선택입니다." << endl;
				continue;
			}

			Monster* target = monsters[targetIndex - 1];

			// 플레이어 공격
			cout << Player->getName() << "이(가) " << target->getName() << "을(를) 공격합니다! ";
			target->takeDamage(Player->getAttack());

			if (target->getHealth() <= 0)
			{
				cout << target->getName() << " 처치!" << endl;
				totalExp += 50;  // 몬스터당 50 경험치
				defeatedCount++;

				delete target;
				monsters.erase(monsters.begin() + targetIndex - 1);

				if (monsters.empty())
				{
					cout << endl << "모든 몬스터를 처치했습니다!" << endl;
					cout << "총 " << defeatedCount << "마리 처치!" << endl;
					reward(Player, totalExp);  // 총 경험치 한번에 지급
					return;
				}
			}
			else
			{
				cout << target->getName() << " 체력: " << target->getHealth() << endl;
			}

			// 남은 몬스터들의 반격
			cout << endl << "--- 몬스터들의 반격! ---" << endl;
			for (Monster* monster : monsters)
			{
				cout << monster->getName() << "이(가) " << Player->getName() << "을(를) 공격합니다! ";
				int tempHealth = Player->getHealth();
				Player->takeDamage(monster->getAttack());
				cout << "데미지: " << monster->getAttack()
					<< " (체력: " << tempHealth << " -> " << Player->getHealth() << ")" << endl;

				if (Player->getHealth() <= 0)
				{
					cout << Player->getName() << "이 쓰러졌습니다. 게임 오버!" << endl;

					// 메모리 정리
					for (Monster* m : monsters)
					{
						delete m;
					}
					monsters.clear();

					exit(0);
				}
			}
			break;
		}

		case 2:
		{
			cout << "게임을 종료합니다." << endl;

			// 메모리 정리
			for (Monster* m : monsters)
			{
				delete m;
			}
			monsters.clear();

			exit(0);
		}
			break;

		default:
			cout << "잘못된 선택입니다. 1 또는 2를 선택해주세요." << endl;
			break;
		}

	}
}

// 기존 단일 전투 (수정된 battle 메소드)
void GameManager::battle(Character* Player)
{
	// 30% 확률로 다중 몬스터 전투
	int battleType = randNum(1, 10);

	if (battleType <= 3)  // 30% 확률
	{
		cout << "!! 경고: 다수의 몬스터 출현 !!" << endl;
		vector<Monster*> monsters = generateMultipleMonsters(Player->getLevel());
		multiBattle(Player, monsters);
	}
	else  // 70% 확률로 기존 단일 전투
	{
		int tempHealth;
		Monster* monster = generateMonster(Player->getLevel());
		cout << "야생 " << monster->getName() << " 출현! 체력: " << monster->getHealth()
			<< ", 공격력: " << monster->getAttack() << endl;

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
				// 플레이어 공격
				cout << Player->getName() << "이(가) " << monster->getName() << "을(를) 공격합니다! ";
				monster->takeDamage(Player->getAttack());

				if (monster->getHealth() <= 0)
				{
					cout << monster->getName() << " 처치!" << endl;
					delete monster;
					reward(Player, 50);
					return;
				}
				else
				{
					cout << monster->getName() << " 체력: " << monster->getHealth() << endl;
				}

				// 몬스터 공격
				cout << monster->getName() << "이(가) " << Player->getName() << "을(를) 공격합니다! ";
				tempHealth = Player->getHealth();
				Player->takeDamage(monster->getAttack());

				if (Player->getHealth() <= 0)
				{
					cout << Player->getName() << " 체력: " << tempHealth << " -> " << Player->getHealth() << endl;
					cout << Player->getName() << "이 쓰러졌습니다. 게임 오버!" << endl;
					delete monster;
					exit(0);
				}
				else
				{
					cout << Player->getName() << " 체력: " << Player->getHealth() << endl;
				}
				break;

			case 2:
				cout << "게임을 종료합니다." << endl;
				delete monster;
				exit(0);
				break;

			default:
				cout << "잘못된 선택입니다. 1 또는 2를 선택해주세요." << endl;
				break;
			}
		}
	}
}

void GameManager::displayInventory(Character* Player)
{
	// 인벤토리 디스플레이 시스템
	cout << "=== 인벤토리 ===" << endl;
	cout << "기능 미구현" << endl;
}

void GameManager::reward(Character* Player, int exp)
{
	int ran = randNum(20, 30);

	// 경험치 및 골드 보상 시스템
	Player->setExperience(exp);
	Player->setGold(ran);

	cout << "전투 승리 : 경험치 " << exp << " 획득, 골드: " << ran << "G 획득!" << endl;

	// 아이템 획득 확률 30%
	ran = randNum(1, 10);
	if (ran >= 1 && ran <= 3)
		cout << "아이템 획득!" << endl;
	else
		cout << "아이템 획득 실패!" << endl;
}

int GameManager::randNum(int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}