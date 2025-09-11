#include "GameManager.h"
#include "GameLogger.h"
#include <iostream>
#include "Character.h"
#include "Knight.h"
#include "Alchemist.h"
#include "Pirate.h"
#include "Farmer.h"
#include "Shop.h"

// ▼ BGM용 헤더/링크 추가
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

// [파일 배치 안내]
// 빌드 후 생성된 .exe 와 같은 폴더에 moon.wav 를 둡니다.
// 예) x64/Debug/YourGame.exe
//     x64/Debug/moon.wav

Character* Character::instance = nullptr;

int main()
{
	// ▼ 프로그램 시작과 동시에 BGM 무한 루프 (비동기)
	PlaySoundW(L"moon.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
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
			// ▼ 종료 직전 BGM 정지
			PlaySoundW(NULL, NULL, 0);
			return 0;
		default:
			cout << "잘못된 선택입니다.\n";
		}
	}
	// (안전 차원에서 한 번 더 정지)
	PlaySoundW(NULL, NULL, 0);
	return 0;
}