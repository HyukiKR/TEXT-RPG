#include "GameManager.h"
#include "GameLogger.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

Monster* GameManager::generateMonster(int level)
{
	int ran = randNum(0, 8);

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
	case 4:
		return new Zombie(level);
	case 5:
		return new SkeletonWarrior(level);
	case 6:
		return new Lizardmen(level);
	case 7:
		return new Wolf(level);
	case 8:
		return new Magmagollem(level);
	}
}

void GameManager::handleAfterBattle(Character* Player)
{
	UI ui;
	while (true)
	{
		system("cls");
		
		int choice = ui.afterMatchDisplay();

		switch (choice)
		{
		case 1: // 상점 방문
		{
			system("cls");
			Shop shop;

			// 직업별로 상점 재고 설정
			string jobName = Player->getJobName();
			if (jobName == "기사" || jobName == "Knight") {
				shop.setStockForJob(Job::Knight, 2, 2);
			}
			else if (jobName == "연금술사" || jobName == "Alchemist") {
				shop.setStockForJob(Job::Alchemist, 3, 2);  // 연금술사는 아이템이 더 많음
			}
			else if (jobName == "해적" || jobName == "Pirate") {
				shop.setStockForJob(Job::Pirate, 2, 2);
			}
			else if (jobName == "농부" || jobName == "Farmer") {
				shop.setStockForJob(Job::Farmer, 2, 2);
			}

			int playerGold = Player->getGold();
			Inventory& inv = Player->getInventory();  // 실제로는 Player의 인벤토리를 가져와야 함
			shop.open(playerGold, inv);
			Player->setGold(playerGold);  // 골드 업데이트

			cout << "\n상점을 나왔습니다. 다음 전투로 진행합니다..." << endl;
			cout << "======================================\n" << endl;
			battle(Player);  // 상점 후 자동으로 다음 전투
			return;
		}
		case 2: // 다음 전투 진행
			system("cls");
			ui.SetColor(12);
			cout << "다음 전투가 임박했습니다" << endl << endl;
			ui.SetColor(15);
			system("pause");
			battle(Player);
			return;
		}
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
	UI ui;
	GameLogger* logger = GameLogger::getInstance();
	int totalExp = 0;
	int defeatedCount = 0;

	cout << endl << "=== 다중 몬스터 전투 시작! ===" << endl;

	while (!monsters.empty() && Player->getHealth() > 0)
	{
		int choice = ui.multiBattleDisplay(Player, monsters);

		//캐릭터 스크롤 사용 효과 저장용 변수
		int scroll = 0;
		int debuff = 0;

		switch (choice)
		{
		case 1:
		{

			int targetIndex = ui.pickMonsterDisplay(Player, monsters);

			Monster* target = monsters[targetIndex - 1];

			system("cls");

			cout << "전투 결과" << endl;
			cout << "======================" << endl << endl;
			cout << "> " << Player->getName() << "가(이) " << target->getName() << "를(을) 상대로 공격합니다." << endl;
			cout << "> " << target->getName() << "는(은) ";
			ui.SetColor(12);
			cout << Player->getAttack() + Player->getAttackBoost();
			ui.SetColor(15);
			cout << "의 피해를 입었습니다." << endl << endl;

			target->takeDamage(Player->getAttack() + Player->getAttackBoost());

			cout << "> " << target->getName() << "의 현재 HP" << endl;
			cout << "HP: ";
			ui.SetColor(10);
			cout << target->getHealth() << "/" << target->getMaxHealth() << endl << endl;
			ui.SetColor(15);

			if (target->getHealth() <= 0)
			{
				cout << "> " << target->getName() << "를(을) 처치했습니다." << endl << endl;
				logger->logBattle(target->getName(), true);  // 로그 추가
				totalExp += 50;  // 몬스터당 50 경험치
				defeatedCount++;

				delete target;
				monsters.erase(monsters.begin() + targetIndex - 1);
				//
				if (monsters.empty())
				{
					cout << endl << "모든 몬스터를 처치하였습니다!" << endl;
					cout << "총 " << defeatedCount << "마리 처치!" << endl << endl;
					reward(Player, totalExp);  // 총 경험치 한번에 지급

					cout << endl << "======================" << endl << endl;
					system("pause");

					// 전투 후 선택
					handleAfterBattle(Player);
					return;
				}
			}

			// 남은 몬스터들의 반격
			for (Monster* monster : monsters)
			{
				cout << "> " << monster->getName() << "가(이) " << Player->getName() << "를(을) 공격합니다." << endl;
				cout << "> " << Player->getName() << "는(은)";
				ui.SetColor(12);
				cout << Player->getAttack() + debuff;
				ui.SetColor(15);
				cout << "의 피해를 입었습니다." << endl << endl;

				Player->takeDamage(monster->getAttack() + debuff);

				if (Player->getHealth() <= 0)
				{
					cout << Player->getName() << "가 사망하였습니다. 게임 오버!" << endl;
					logger->logBattle("플레이어 사망", false);  // 로그 추가

					// 메모리 해제
					for (Monster* m : monsters)
					{
						delete m;
					}
					monsters.clear();

					exit(0);
				}
			}
			cout << "> " << Player->getName() << "의 현재 HP: ";
			ui.SetColor(10);
			cout << Player->getHealth() << endl;
			ui.SetColor(15);

			cout << endl << "======================" << endl << endl;
			system("pause");
			break;
		}

		case 2:
		{
			//Inventory& inv = Player->getInventory();
			//inv.showItemsSimple();
			Player->useItemFromInventory();

			scroll = Player->getScroll(); // 스크롤 사용 여부 상태

			if (scroll > 0) // 광역공격
			{
				vector<Monster*> toDelete;

				for (Monster* monster : monsters)
				{
					monster->takeDamage(scroll);

					if (monster->getHealth() <= 0)
					{
						cout << monster->getName() << " 처치!" << endl;
						logger->logBattle(monster->getName(), true);  // 로그 추가
						totalExp += 50;  // 몬스터당 50 경험치
						defeatedCount++;

						toDelete.push_back(monster);
					}
					else
					{
						cout << monster->getName() << " 체력: " << monster->getHealth() << endl;
					}
				}

				// 체력이 0인 개체 삭제
				for (Monster* m : toDelete)
				{
					monsters.erase(std::remove(monsters.begin(), monsters.end(), m), monsters.end());
				}

				//몬스터 처치여부 확인
				if (monsters.empty())
				{
					cout << endl << "모든 몬스터를 처치하였습니다!" << endl;
					cout << "총 " << defeatedCount << "마리 처치!" << endl;
					reward(Player, totalExp);  // 총 경험치 한번에 지급

					// 전투 후 선택
					handleAfterBattle(Player);
					return;
				}

			}
			else if (scroll < 0) // 몬스터 공격력 디버프
			{
				debuff = scroll;
			}

			Player->setScroll(0);
			break;
		}

		case 3:
		{
			cout << "게임을 종료합니다." << endl;

			// 메모리 해제
			for (Monster* m : monsters)
			{
				delete m;
			}
			monsters.clear();

			exit(0);
			break;		
		}			

		default:
			cout << "잘못된 선택입니다. 1 또는 2를 입력해주세요." << endl;
			break;
		}


	}
}

// 단일 몬스터 전투 (기존 battle 함수)
void GameManager::battle(Character* Player)
{
	GameLogger* logger = GameLogger::getInstance();
	UI ui;

	// 30% 확률로 다중 몬스터 전투
	int battleType = randNum(1, 10);

	if (battleType <= 3)  // 30% 확률
	{
		system("cls");
		ui.SetColor(14);
		cout << "!! 경고: 다중 몬스터 전투 발생 !!" << endl;
		Sleep(1500);
		ui.SetColor(15);
		vector<Monster*> monsters = generateMultipleMonsters(Player->getLevel());
		multiBattle(Player, monsters);
	}
	else  // 70% 확률로 단일 몬스터 전투
	{
		Monster* monster = generateMonster(Player->getLevel());

		system("cls");

		ui.SetColor(14);
		cout << "!몬스터가 출몰합니다!" << endl << endl;
		Sleep(1500);
		cout << "<<" << monster->getIntro() << ">>" << endl << endl;
		Sleep(1500);
		cout << monster->getName() << "이(가) 나타났다!" << endl;
		Sleep(1500);
		ui.SetColor(15);

		while (true)
		{
			system("cls");

			int choice = ui.singleBattleDisplay(Player, monster);

			//캐릭터 스크롤 사용 효과 저장용 변수
			int scroll = 0;
			int debuff = 0;

			switch (choice)
			{
			case 1:
			{	// 플레이어 공격
				system("cls");

				cout << "전투 결과" << endl;
				cout << "======================" << endl << endl;
				cout << "> " << Player->getName() << "가(이) " << monster->getName() << "를(을) 상대로 공격합니다." << endl;
				cout << "> " << monster->getName() << "는(은) ";
				ui.SetColor(12);
				cout << Player->getAttack() + Player->getAttackBoost();
				ui.SetColor(15);
				cout << "의 피해를 입었습니다." << endl << endl;

				monster->takeDamage(Player->getAttack() + Player->getAttackBoost());

				cout << "> " << monster->getName() << "의 현재 HP" << endl;
				cout << "HP: ";
				ui.SetColor(10);
				cout << monster->getHealth() << "/" << monster->getMaxHealth() << endl << endl;
				ui.SetColor(15);

				if (monster->getHealth() <= 0)
				{
					cout << "> " << monster->getName() << "를(을) 처치했습니다." << endl;
					logger->logBattle(monster->getName(), true);  // 로그 추가
					delete monster;
					reward(Player, 50);

					cout << endl << "======================" << endl << endl;
					system("pause");

					// 전투 후 선택
					handleAfterBattle(Player);
					return;
				}

				// 몬스터 반격
				cout << "> " << monster->getName() << "가(이) " << Player->getName() << "를(을) 공격합니다." << endl;
				cout << "> " << Player->getName() << "는(은)";
				ui.SetColor(12);
				cout << Player->getAttack() + debuff;
				ui.SetColor(15);
				cout << "의 피해를 입었습니다." << endl << endl;

				Player->takeDamage(monster->getAttack() + debuff);

				cout << "> " << Player->getName() << "의 현재 HP: ";
				ui.SetColor(10);
				cout << Player->getHealth() << endl;
				ui.SetColor(15);

				if (Player->getHealth() <= 0)
				{
					cout << "> " << Player->getName() << "가 사망하였습니다. 게임 오버!" << endl;
					cout << endl << "======================" << endl;
					logger->logBattle(monster->getName(), false);  // 로그 추가
					delete monster;
					exit(0);
				}
				cout << endl << "======================" << endl << endl;
				system("pause");
				break;
			}
			case 2:
			{
				//Inventory& inv = Player->getInventory();
				//inv.showItemsSimple();
				Player->useItemFromInventory();

				scroll = Player->getScroll(); // 스크롤 사용 여부 상태

				if (scroll > 0) // 광역공격
				{
					monster->takeDamage(scroll);

					if (monster->getHealth() <= 0)
					{
						cout << monster->getName() << " 처치!" << endl;
						logger->logBattle(monster->getName(), true);  // 로그 추가
						delete monster;
						reward(Player, 50);

						// 전투 후 선택
						handleAfterBattle(Player);
						return;
					}
					else
					{
						cout << monster->getName() << " 체력: " << monster->getHealth() << endl;
					}
				}
				else if (scroll < 0) // 몬스터 공격력 디버프
				{
					debuff = scroll;
				}

				Player->setScroll(0);

				break;
			}

			case 3:
			{
				cout << "게임을 종료합니다." << endl;
				delete monster;
				exit(0);
				break;
			}
			default:
				cout << "잘못된 선택입니다. 1 또는 2를 입력해주세요." << endl;
				break;				
			}
		}
	}
}

void GameManager::displayInventory(Character* Player)
{
	// 인벤토리 간단 출력 시스템
	cout << "=== 인벤토리 ===" << endl;
	cout << "현재 아이템" << endl;
}

void GameManager::reward(Character* Player, int exp)
{
	GameLogger* logger = GameLogger::getInstance();
	UI ui;
	int ran = randNum(20, 30);

	// 경험치 및 골드 지급 시스템
	Player->setExperience(exp);
	Player->setGold(ran);

	// 로그 기록
	logger->logExpEarned(exp);
	logger->logGoldEarned(ran);

	cout << "전투 보상 : 경험치 ";
	ui.SetColor(9);
	cout << exp;
	ui.SetColor(15);
	cout << " 획득, 골드: ";
	ui.SetColor(14);
	cout << ran << "G";
	ui.SetColor(15);
	cout << " 획득" << endl << endl;

	// 아이템 획득 확률 30%
	ran = randNum(1, 10);
	if (ran >= 1 && ran <= 3) 
	{
		cout << "아이템 획득" << endl;
		logger->logItemFound("특별 아이템");
	}
	else
		cout << "아이템 획득 실패" << endl;
}

int GameManager::randNum(int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}