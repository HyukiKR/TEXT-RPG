#pragma once
#ifndef UI_H
#define UI_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "Character.h"
#include "Monster.h"
#include "Item.h"

class UI
{
public:
	void displayIntro();
	int characterSetDisplay(std::string& tempName);
	int mainMenuDisplay();
	int singleBattleDisplay(Character* Player, Monster* monster);
	int afterMatchDisplay();
	void SetColor(int colorNumber);
	int ShopMenuDisplay();
	int multiBattleDisplay(Character* Player, vector<Monster*>& monsters);
	int pickMonsterDisplay(Character* Player, vector<Monster*>& monsters);
	int buyDisplay(vector<Item*>& items);
	int sellDisplay(vector<const Item*> items);
};

#endif // !UI_H
