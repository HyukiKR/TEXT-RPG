#include "GameManager.h"
#include "GameLogger.h"
#include <iostream>
#include "Character.h"
#include "Knight.h"
#include "Alchemist.h"
#include "Pirate.h"
#include "Farmer.h"
#include "Intro.h"
#include "Shop.h"

using namespace std;

Character* Character::instance = nullptr;

int main()
{
	GameManager gameManager;
	GameLogger* logger = GameLogger::getInstance();
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
	logger->logJobSelected(player->getJobName());  // 로그 추가

	cout << player->getJobName() << " " << name << " 생성 완료! 레벨: " << player->getLevel() << ", 체력: " <<
		player->getHealth() << ", 공격력: " << player->getAttack() << endl << endl;

	// 게임 루프
	while (true) {
		cout << "\n===== 메인 메뉴 =====\n";
		cout << "1. 전투\n";
		cout << "2. 상태 확인\n";
		cout << "3. 상점\n";
		cout << "4. 인벤토리\n";
		cout << "5. 로그 확인\n";
		cout << "6. 전투 기록\n";
		cout << "7. 로그 저장\n";
		cout << "8. 종료\n";
		cout << "선택: ";

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			gameManager.battle(player);
			break;
		case 2:
			player->displayStatus();
			break;
		case 3:
		{
			Shop shop;
			int playerGold = player->getGold();
			Inventory inv;
			shop.open(playerGold, inv);
			player->setGold(playerGold - player->getGold());
			break;
		}
		case 4:
			gameManager.displayInventory(player);
			break;
		case 5:
			logger->displayLogs();
			break;
		case 6:
			logger->displaySummary();
			logger->displayMonsterKills();
			logger->displayShopHistory();
			break;
		case 7:
			logger->saveLogsToFile();
			break;
		case 8:
			logger->saveLogsToFile();
			cout << "게임을 종료합니다.\n";
			return 0;
		default:
			cout << "잘못된 선택입니다.\n";
		}
	}

	return 0;
}