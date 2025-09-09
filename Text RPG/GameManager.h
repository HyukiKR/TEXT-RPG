#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Character.h"
#include "Monster.h"
#include "Goblin.h"
#include "Troll.h"
#include "Orc.h"
#include "Slime.h"
#include "inventory.h"
#include <vector>

class GameManager {
public:
	Monster* generateMonster(int level);
	std::vector<Monster*> generateMultipleMonsters(int playerLevel);  // 추가
	void battle(Character* Player);
	void multiBattle(Character* Player, std::vector<Monster*>& monsters);  // 추가
	void displayInventory(Character* Player);
	void reward(Character* Player, int exp);
	int randNum(int min, int max);
};
#endif // !GAMEMANAGER_H