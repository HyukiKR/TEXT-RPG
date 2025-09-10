#include "GameManager.h"
#include "GameLogger.h"
#include "BossMonster.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// 전투 화면에 출력되는 디스플레이
void displayBattleChoice()
{
	cout << endl << "---------------------------" << endl;
	cout << "Battle logic" << endl;
	cout << "1. 공격" << endl;
	cout << "2. 인벤토리 확인" << endl;
	cout << "3. 게임 종료" << endl;
	cout << "---------------------------" << endl << endl;
	cout << "선택: ";
}


void displayAfterBattleChoice()
{
	cout << endl << "===== 전투 승리! =====" << endl;
	cout << "무엇을 하시겠습니까?" << endl;
	cout << "1. 상점 방문" << endl;
	cout << "2. 다음 전투 진행" << endl;
	cout << "======================" << endl;
	cout << "선택: ";
}


Monster* GameManager::generateMonster(int level)
{
	int ran = randNum(0, 9);

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

// 보스몬스터
Monster* GameManager::generateBossMonster(int level) {
	return new BossMonster(level); 
}

void GameManager::handleAfterBattle(Character* Player)
{
	while (true)
	{
		displayAfterBattleChoice();
		int choice;
		cin >> choice;

		if (cin.fail()) {
			cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		switch (choice)
		{
		case 1: // 상점 방문
		{
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
			cout << "\n다음 전투로 진행합니다..." << endl;
			cout << "======================================\n" << endl;
			battle(Player);
			return;
		default:
			cout << "잘못된 선택입니다. 1 또는 2를 선택해주세요." << endl;
			break;
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
	GameLogger* logger = GameLogger::getInstance();
	int totalExp = 0;
	int defeatedCount = 0;

	cout << endl << "=== 다중 몬스터 전투 시작! ===" << endl;

	while (!monsters.empty() && Player->getHealth() > 0)
	{
		// 남은 몬스터 목록 표시
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

		//캐릭터 스크롤 사용 효과 저장용 변수
		int scroll = 0;
		int debuff = 0;

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
                cout << "잘못된 입력입니다." << endl;
				continue;
			}

			Monster* target = monsters[targetIndex - 1];

			// 플레이어 공격
			Player->attackMassage();
			cout << Player->getName() << "가(이) " << target->getName() << "를(을) 공격합니다! ";
			target->takeDamage(Player->getAttack()+Player->getAttackBoost());

			if (target->getHealth() <= 0)
			{
				cout << target->getName() << " 처치!" << endl;
				logger->logBattle(target->getName(), true);  // 로그 추가
				totalExp += 50;  // 몬스터당 50 경험치
				defeatedCount++;

				delete target;
				monsters.erase(monsters.begin() + targetIndex - 1);

				if (monsters.empty())
				{
					cout << endl << "모든 몬스터를 처치하였습니다!" << endl;
					cout << "총 " << defeatedCount << "마리 처치!" << endl;
					reward(Player, totalExp);  // 총 경험치 한번에 지급

					monstersDefeated += defeatedCount; // 죽인 몬스터 수 증가
					checkBossBattle(Player); // 보스 등장 체크

					// 전투 후 선택
					handleAfterBattle(Player);
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
				cout << monster->getName() << "가(이) " << Player->getName() << "를(을) 공격합니다! ";
				int tempHealth = Player->getHealth();
				Player->takeDamage(monster->getAttack() + debuff);
				cout << "공격력: " << monster->getAttack() + debuff
					<< " (체력: " << tempHealth << " -> " << Player->getHealth() << ")" << endl;

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

			//턴 종료시 패시브 스킬 발동 및 공격력 부스트, 디버프 초기화
			Player->passiveSkill();
			Player->boostAttack(0);
			debuff = 0;
			
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
				for (Monster* monster : monsters)
				{
					monster->takeDamage(scroll);
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

	// 30% 확률로 다중 몬스터 전투
	int battleType = randNum(1, 10);

	if (battleType <= 3)  // 30% 확률
	{
		cout << "!! 경고: 다중 몬스터 전투 발생 !!" << endl;
		vector<Monster*> monsters = generateMultipleMonsters(Player->getLevel());
		multiBattle(Player, monsters);
	}
	else  // 70% 확률로 단일 몬스터 전투
	{
		int tempHealth;
		Monster* monster = generateMonster(Player->getLevel());

		cout << "<<" << monster->getIntro() << ">>" << endl;
		cout << "출현 " << monster->getName() << " 등장! 체력: " << monster->getHealth()
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

			//캐릭터 스크롤 사용 효과 저장용 변수
			int scroll = 0;   
			int debuff = 0;

			switch (choice)
			{
			case 1:
			{	
				// 플레이어 공격
				Player->attackMassage();
				cout << Player->getName() << "가(이) " << monster->getName() << "를(을) 공격합니다! ";
				monster->takeDamage(Player->getAttack() + Player->getAttackBoost());

				if (monster->getHealth() <= 0)
				{
					cout << monster->getName() << " 처치!" << endl;
					logger->logBattle(monster->getName(), true);  // 로그 추가
					delete monster;
					reward(Player, 50);

					monstersDefeated++; // 한 마리 처치!
					checkBossBattle(Player); // 보스 등장 체크

					// 전투 후 선택
					handleAfterBattle(Player);
					return;
				}
				else
				{
					cout << monster->getName() << " 체력: " << monster->getHealth() << endl;
				}

				// 몬스터 반격
				cout << monster->getName() << "가(이) " << Player->getName() << "를(을) 공격합니다! ";
				tempHealth = Player->getHealth();
				Player->takeDamage(monster->getAttack() + debuff);

				if (Player->getHealth() <= 0)
				{
					cout << Player->getName() << " 체력: " << tempHealth << " -> " << Player->getHealth() << endl;
					cout << Player->getName() << "가 사망하였습니다. 게임 오버!" << endl;
					logger->logBattle(monster->getName(), false);  // 로그 추가
					delete monster;
					exit(0);
				}
				else
				{
					cout << Player->getName() << " 체력: " << Player->getHealth() << endl;
				}

				//턴 종료시 패시브 스킬 발동 및 공격력 부스트, 디버프 초기화
				Player->passiveSkill();
				Player->boostAttack(0);
				debuff = 0;

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

void GameManager::checkBossBattle(Character* Player)
{
	if (monstersDefeated >= bossThreshold)
	{
		cout << "\n!!! 경고: 마왕 등장 !!!\n" << endl;
		Monster* boss = generateBossMonster(Player->getLevel() + 2);  // 레벨 약간 높게
		cout << "마왕 " << boss->getName() << " 출현! 체력: " << boss->getHealth()
			<< ", 공격력: " << boss->getAttack() << endl;

		// 단일 보스 전투 진행
		battleBoss(Player, boss);

		// 보스 처치 후 카운트 초기화
		monstersDefeated = 0;
	}
}

// 보스 전용 전투 함수
void GameManager::battleBoss(Character* Player, Monster* boss)
{
	GameLogger* logger = GameLogger::getInstance();
	int tempHealth;

	while (boss->getHealth() > 0 && Player->getHealth() > 0)
	{
		displayBattleChoice();
		int choice;
		cin >> choice;

		if (cin.fail()) {
			cout << "잘못된 입력입니다. 숫자를 입력해주세요." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		switch (choice)
		{
		case 1:
			// 플레이어 공격
			cout << Player->getName() << "가 " << boss->getName() << "를 공격합니다! ";
			boss->takeDamage(Player->getAttack());

			if (boss->getHealth() <= 0)
			{
				cout << boss->getName() << " 처치!" << endl;
				logger->logBattle(boss->getName(), true);
				reward(Player, 200); // 보스 보상
				delete boss;
				return;
			}
			else
				cout << boss->getName() << " 체력: " << boss->getHealth() << endl;

			// 보스 반격
			cout << boss->getName() << "가 " << Player->getName() << "를 공격합니다! ";
			tempHealth = Player->getHealth();
			Player->takeDamage(boss->getAttack());
			cout << "공격력: " << boss->getAttack()
				<< " (체력: " << tempHealth << " -> " << Player->getHealth() << ")" << endl;

			if (Player->getHealth() <= 0)
			{
				cout << Player->getName() << "가 사망하였습니다. 게임 오버!" << endl;
				logger->logBattle(boss->getName(), false);
				delete boss;
				exit(0);
			}
			break;

		case 2:
			Player->getInventory().showItemsSimple();
			break;

		case 3:
			cout << "게임을 종료합니다." << endl;
			delete boss;
			exit(0);
			break;

		default:
			cout << "잘못된 선택입니다. 1~3을 입력해주세요." << endl;
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
	int ran = randNum(20, 30);

	// 경험치 및 골드 지급 시스템
	Player->setExperience(exp);
	Player->setGold(ran);

	// 로그 기록
	logger->logExpEarned(exp);
	logger->logGoldEarned(ran);

	cout << "전투 보상 : 경험치 " << exp << " 획득, 골드: " << ran << "G 획득!" << endl;

	// 아이템 획득 확률 30%
	ran = randNum(1, 10);
	if (ran >= 1 && ran <= 3) 
	{
		cout << "아이템 획득!" << endl;
		logger->logItemFound("특별 아이템");
	}
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