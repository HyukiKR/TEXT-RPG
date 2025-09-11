#include "UI.h"

//유저가 입력한 키 값을 정의
#define KEY_ARROWKEY 224
#define KEY_UP 72 
#define KEY_DOWN 80
#define KEY_ENTER 13

using namespace std;

int getConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// 텍스트를 오른쪽 정렬로 출력하는 함수
int textPadding(int selected, int addLength, const string& text)
{
	int consoleWidth = getConsoleWidth();

	int textLength = text.length() + addLength;

	int padding = (consoleWidth > textLength) ? (consoleWidth - textLength) : 0;

	return padding;
}

void UI::displayIntro()
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장

	int key;  // 키 입력 받기

	while (true)
	{
		system("cls"); // 화면 지우기

		cout << R"(

 _   __ _____  _   _  _____  ______  _   _  _   _ 
| | / /|_   _|| \ | ||  __ \ | ___ \| | | || \ | |
| |/ /   | |  |  \| || |  \/ | |_/ /| | | ||  \| |
|    \   | |  | . ` || | __  |    / | | | || . ` |
| |\  \ _| |_ | |\  || |_\ \ | |\ \ | |_| || |\  |
\_| \_/ \___/ \_| \_/ \____/ \_| \_| \___/ \_| \_/                                                                                                    
)" << endl;


		int padding = textPadding(selected, 30, "1. 게임 시작");

		cout << string(padding, ' ') << (selected == 0 ? "> " : "  ") << "1. 시작" << endl;
		cout << string(padding, ' ') << (selected == 1 ? "> " : "  ") << "2. 종료" << endl;


		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				selected = 1;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			if (selected == 0) // 게임 종료 선택 시
			{
				system("cls");
				break;
			}
			else if (selected == 1) // 게임 시작 선택 시
			{
				system("cls");
				cout << "게임을 종료합니다.\n";
				exit(0);
			}
		}
	}
}

// 텍스트 색상 바꾸는 함수
void UI::SetColor(int colorNumber)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNumber);
}

int UI::characterSetDisplay(string& tempName)
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 3; // 선택할 수 있는 최대 메뉴 수 - 1

	int key;

	SetColor(9);
	cout << "<캐릭터를 생성합니다>" << endl << endl;
	SetColor(15);
	cout << "> 이름을 입력해주세요: ";
	cin >> tempName;

	cout << endl << "직업을 선택해주세요" << endl << endl;

	while (true)
	{
		system("cls"); // 화면 지우기		

		SetColor(9);
		cout << "<캐릭터를 생성합니다>" << endl << endl;
		SetColor(15);
		cout << "> 이름을 입력해주세요: " << tempName << endl;
		cout << endl << "직업을 선택해주세요" << endl;

		cout << (selected == 0 ? "> " : "  ") << "1. 기사" << endl;
		cout << (selected == 1 ? "> " : "  ") << "2. 연금술사" << endl;
		cout << (selected == 2 ? "> " : "  ") << "3. 해적" << endl;
		cout << (selected == 3 ? "> " : "  ") << "4. 농부" << endl;


		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}

	SetColor(10);
	cout << endl << "> 캐릭터 생성이 완료되었습니다." << endl;
	Sleep(1000);
	cout << "> 게임을 시작합니다...";
	SetColor(15);
	Sleep(1000);

	return selected + 1;
}

int UI::mainMenuDisplay()
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 7; // 선택할 수 있는 최대 메뉴 수 - 1

	int key;

	while (true)
	{
		system("cls");

		SetColor(9);
		cout << "       메뉴 선택창" << endl;
		SetColor(15);
		cout << "========================" << endl << endl;

		cout << (selected == 0 ? "   > " : "      ") << "1. 전투" << endl;
		cout << (selected == 1 ? "   > " : "      ") << "2. 상태 확인" << endl;
		cout << (selected == 2 ? "   > " : "      ") << "3. 상점" << endl;
		cout << (selected == 3 ? "   > " : "      ") << "4. 인벤토리" << endl;
		cout << (selected == 4 ? "   > " : "      ") << "5. 로그 확인" << endl;
		cout << (selected == 5 ? "   > " : "      ") << "6. 전투 기록" << endl;
		cout << (selected == 6 ? "   > " : "      ") << "7. 로그 저장" << endl;
		cout << (selected == 7 ? "   > " : "      ") << "8. 종료" << endl << endl;

		cout << "========================" << endl;

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}

	return selected + 1;
}

int UI::afterMatchDisplay()
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 1; // 선택할 수 있는 최대 메뉴 수 - 1

	int key;

	while (true)
	{
		system("cls");

		cout << endl << "===== ";
		SetColor(14);
		cout << "전투 승리! ";
		SetColor(15);
		cout << "=====" << endl;

		cout << (selected == 0 ? " > " : "     ") << "1. 상점 방문" << endl;
		cout << (selected == 1 ? " > " : "     ") << "2. 다음 전투 진행" << endl;
		cout << "======================" << endl;

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}

	return selected + 1;
}

int UI::singleBattleDisplay(Character* Player, Monster* monster)
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 2; // 선택할 수 있는 최대 메뉴 수 - 1
	int key;


	while (true)
	{
		system("cls");

		cout << "몬스터" << endl;
		cout << "======================" << endl << endl;
		cout << "> " << monster->getName() << endl;
		cout << "HP: ";
		SetColor(10);
		cout << monster->getHealth() << "/" << monster->getMaxHealth();
		SetColor(15);
		cout << " ATK: " << monster->getAttack() << endl << endl;
		cout << "======================" << endl << endl;
		cout << "> " << Player->getName() << "의 스텟" << endl;
		cout << "HP: ";
		SetColor(10);
		cout << Player->getHealth() << "/" << Player->getMaxHealth();
		SetColor(15);
		cout << " ATK: " << Player->getAttack() << endl;

		int padding = textPadding(selected, 50, "1. 공격한다");

		cout << string(padding, ' ') << " ================" << endl;

		cout << string(padding, ' ') << (selected == 0 ? "> " : "   ") << "1. 공격한다" << endl;
		cout << string(padding, ' ') << (selected == 1 ? "> " : "   ") << "2. 아이템 사용" << endl;
		cout << string(padding, ' ') << (selected == 2 ? "> " : "   ") << "3. 도망친다" << endl;

		cout << string(padding, ' ') << " ================" << endl;

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}
	return selected + 1;
}

int UI::ShopMenuDisplay()
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 3; // 선택할 수 있는 최대 메뉴 수 - 1
	int key;

	while (true)
	{
		system("cls");

		SetColor(9);
		cout << "       <상점 메뉴>" << endl;
		SetColor(15);
		cout << "========================" << endl << endl;

		cout << (selected == 0 ? "   > " : "      ") << "1. 구매" << endl;
		cout << (selected == 1 ? "   > " : "      ") << "2. 판매" << endl;
		cout << (selected == 2 ? "   > " : "      ") << "3. 인벤토리 보기" << endl;
		cout << (selected == 3 ? "   > " : "      ") << "4. 나가기" << endl << endl;

		cout << "========================" << endl;

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}

	return selected + 1;
}

int UI::multiBattleDisplay(Character* Player, vector<Monster*>& monsters)
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 2; // 선택할 수 있는 최대 메뉴 수 - 1
	int key;

	while (true)
	{
		system("cls");

		cout << "다중 몬스터" << endl;
		cout << "======================" << endl << endl;
		for (int i = 0; i < monsters.size(); i++)
		{
			cout << "> " << (i + 1) << ". " << monsters[i]->getName() << endl;
			cout << "HP: ";
			SetColor(10);
			cout << monsters[i]->getHealth() << "/" << monsters[i]->getMaxHealth();
			SetColor(15);
			cout << " ATK: " << monsters[i]->getAttack() << endl << endl;
		}
		cout << "======================" << endl << endl;
		cout << "> " << Player->getName() << "의 스텟" << endl;
		cout << "HP: ";
		SetColor(10);
		cout << Player->getHealth() << "/" << Player->getMaxHealth();
		SetColor(15);
		cout << " ATK: " << Player->getAttack() << endl;

		int padding = textPadding(selected, 50, "1. 공격한다");

		cout << string(padding, ' ') << " ================" << endl;

		cout << string(padding, ' ') << (selected == 0 ? "> " : "   ") << "1. 공격한다" << endl;
		cout << string(padding, ' ') << (selected == 1 ? "> " : "   ") << "2. 아이템 사용" << endl;
		cout << string(padding, ' ') << (selected == 2 ? "> " : "   ") << "3. 도망친다" << endl;

		cout << string(padding, ' ') << " ================" << endl;

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}
	return selected + 1;
}

int UI::pickMonsterDisplay(Character* Player, vector<Monster*>& monsters)
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = monsters.size() - 1; // 선택할 수 있는 최대 메뉴 수 - 1
	int key;

	while (true)
	{
		system("cls");

		cout << "다중 몬스터" << endl;
		cout << "======================" << endl << endl;
		for (int i = 0; i < monsters.size(); i++)
		{
			cout << "> " << (i + 1) << ". " << monsters[i]->getName() << endl;
			cout << "HP: ";
			SetColor(10);
			cout << monsters[i]->getHealth() << "/" << monsters[i]->getMaxHealth();
			SetColor(15);
			cout << " ATK: " << monsters[i]->getAttack() << endl << endl;
		}
		cout << "======================" << endl << endl;
		cout << "> " << Player->getName() << "의 스텟" << endl;
		cout << "HP: ";
		SetColor(10);
		cout << Player->getHealth() << "/" << Player->getMaxHealth();
		SetColor(15);
		cout << " ATK: " << Player->getAttack() << endl;

		int padding = textPadding(selected, 50, "1. 공격한다");

		cout << string(padding, ' ') << "    공격 대상" << endl;
		cout << string(padding, ' ') << " ================" << endl;

		for (int i = 0; i < monsters.size(); i++)
		{
			cout << string(padding, ' ') << (selected == i ? "> " : "   ") << (i + 1) << ". " << monsters[i]->getName() << endl;
		}

		cout << string(padding, ' ') << " ================" << endl;

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}
	return selected + 1;
}

int UI::buyDisplay(vector<Item*>& items)
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 4; // 선택할 수 있는 최대 메뉴 수 - 1
	int key;

	while (true)
	{
		system("cls");

		if (items.size() == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				cout << (selected == i ? "> " : "   ") << (i + 1) << ". " << "[재고 없음]" << endl;
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (items[i] == nullptr)
				{
					cout << (selected == i ? "> " : "   ") << (i + 1) << ". " << "[재고 없음]" << endl;
				}
				else
				{
					cout << (selected == i ? "> " : "   ") << (i + 1) << ". " << items[i]->getName()
						<< " - ";
					SetColor(14);
					cout << items[i]->getPrice() << "G\n";
					SetColor(15);
				}
			}
		}
		cout << (selected == maxSelection ? "> " : "   ") << "뒤로가기";

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}

	return selected;
}

int UI::sellDisplay(vector<const Item*> items)
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int maxSelection = 5; // 선택할 수 있는 최대 메뉴 수 - 1
	int key;

	while (true)
	{
		system("cls");

		if (items.size() == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				cout << (selected == i ? "> " : "   ") << (i + 1) << ". " << "[비어있음]" << endl;
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				if (items[i] == nullptr)
				{
					cout << (selected == i ? "> " : "   ") << (i + 1) << ". " << "[비어있음]" << endl;
				}
				else
				{
					cout << (selected == i ? "> " : "   ") << (i + 1) << ". " << items[i]->getName() << endl;
				}
			}
		}
		cout << (selected == maxSelection ? "> " : "   ") << "뒤로가기" << endl;

		key = _getch();  // 키 입력 받기 (엔터 누를 필요 없음)

		if (key == KEY_ARROWKEY) // 방향키 입력 처리
		{
			key = _getch(); // 방향키의 두 번째 코드 읽기
			if (key == KEY_UP) { // ↑ 위쪽 화살표
				if (selected > 0)
					selected--;
				else
					selected = 0;
			}
			else if (key == KEY_DOWN) { // ↓ 아래쪽 화살표
				if (selected < maxSelection)
					selected++;
				else
					selected = maxSelection;
			}
		}
		else if (key == KEY_ENTER) // 엔터 키 입력 처리
		{
			break;
		}
	}

	return selected;
}