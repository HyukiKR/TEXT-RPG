#include "Intro.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

//유저가 입력한 키 값을 정의
#define KEY_ARROWKEY 224
#define KEY_UP 72 
#define KEY_DOWN 80
#define KEY_ENTER 13

using namespace std;

// 콘솔 창의 너비를 가져오는 함수
int getConsoleWidth() 
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// 텍스트를 오른쪽 정렬로 출력하는 함수
void printChoice(int selected , const string& text1, const string& text2)
{
	int consoleWidth = getConsoleWidth();

	int textLength1 = text1.length() + 30;
	int textLength2 = text2.length() + 30;

	int padding1 = (consoleWidth > textLength1) ? (consoleWidth - textLength1) : 0;
	int padding2 = (consoleWidth > textLength2) ? (consoleWidth - textLength2) : 0;
	cout << string(padding1, ' ') << (selected == 0 ? "> " : "  ") << text1 << endl;
	cout << string(padding2, ' ') << (selected == 1 ? "> " : "  ") << text2 << endl;
}

void Intro::displayIntro()
{
	int selected = 0; //무슨 메뉴를 선택했는지 저장
	int menuSize = 2; //메뉴의 크기

	int key;  // 키 입력 받기

	while (true)
	{
		system("cls"); // 화면 지우기

		cout << R"(
 _____ _______   _______   ____________ _____ 
|_   _|  ___\ \ / /_   _|  | ___ \ ___ \  __ \
  | | | |__  \ V /  | |    | |_/ / |_/ / |  \/
  | | |  __| /   \  | |    |    /|  __/| | __ 
  | | | |___/ /^\ \ | |    | |\ \| |   | |_\ \
  \_/ \____/\/   \/ \_/    \_| \_\_|    \____/
)" << endl;


		printChoice(selected, "1. 게임 시작", "2. 게임 종료");


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
				cout << "게임을 시작합니다!\n";
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