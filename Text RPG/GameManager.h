#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Character.h"
#include "Monster.h"
#include "Goblin.h"
#include "Troll.h";
#include "Orc.h";
#include "Slime.h";

class GameManager{
public:
	Monster* generateMonster(int level);
	void battle(Character* Player);
	void displayInventory(Character* Player);
};
#endif // !GAMEMANAGER_H