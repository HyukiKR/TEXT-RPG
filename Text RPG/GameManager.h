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
#include "inventory.h"

class GameManager {
public:
	Monster* generateMonster(int level);
	Monster* generateBossMonster(int level);
	void handleAfterBattle(Character* Player);
	std::vector<Monster*> generateMultipleMonsters(int playerLevel);  // 추가
	void battle(Character* Player);
	void checkBossBattle(Character* Player);
	void multiBattle(Character* Player, std::vector<Monster*>& monsters);
	void battleBoss(Character* Player, Monster* boss);
	// 추가
	void displayInventory(Character* Player);
	void reward(Character* Player, int exp);
private:
	int monstersDefeated = 0; //누적 처치수
	int bossThreshold = 5; // 몇 명 잡으면 보스 등장?
	int randNum(int min, int max);
};
#endif // !GAMEMANAGER_H