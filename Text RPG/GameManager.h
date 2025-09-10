#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Character.h"
#include "Monster.h"
#include "Goblin.h"
#include "Troll.h"
#include "Orc.h"
#include "Slime.h"
#include "Zombie.h"
#include "SkeletonWarrior.h"
#include "Lizardmen.h"
#include "Magmagollem.h"
#include "Wolf.h"
#include "Imp.h"
#include "Dragon.h"
#include "Demonlord.h"
#include "Item.h"
#include "Inventory.h"
#include "shop.h"
#include <vector>

class GameManager {
public:
	Monster* generateMonster(int level);
	void handleAfterBattle(Character* Player);
	std::vector<Monster*> generateMultipleMonsters(int playerLevel);  // 추가
	void battle(Character* Player);
	void multiBattle(Character* Player, std::vector<Monster*>& monsters);  // 추가
	void displayInventory(Character* Player);
	void reward(Character* Player, int exp);
	int randNum(int min, int max);
};
#endif // !GAMEMANAGER_H