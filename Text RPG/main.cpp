#include <iostream>
#include <windows.h>
#include "GameManager.h"
#include "GameLogger.h"
#include "Knight.h"
#include "Alchemist.h"
#include "Pirate.h"
#include "Farmer.h"
#include "UI.h"

using namespace std;

Character* Character::instance = nullptr;


int main()
{
	GameManager gameManager;
	UI UI;
	GameLogger* logger = GameLogger::getInstance();
	Monster* monster = nullptr;
	string name;

    UI.displayIntro(); //인트로 화면 출력
	int job_choice = UI.characterSetDisplay(name); //캐릭터 이름 설정 화면 출력

	Character* player = Character::getInstance(name, job_choice);
	logger->logJobSelected(player->getJobName());  // 로그 추가

	// 게임 루프
	while (true) {
		int choice = UI.mainMenuDisplay();

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