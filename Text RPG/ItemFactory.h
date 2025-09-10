#pragma once

#include <vector>
#include "Item.h"

class Item; //전방선언

class ItemFactory {
public:
	//각 직업별 아이템 생성 함수들
	static std::vector<Item> getAlchemistItems();
	static std::vector<Item> getKnightItems();
	static std::vector<Item> getPirateItems();
	static std::vector<Item> getFarmerItems();

	//모든 아이템 가져오기
	static std::vector<Item> getAllItems();

	//타입별 아이템 가져오기
	static std::vector<Item> getAllHealthPotions();
	static std::vector<Item> getAllAttackBoosts();

	//스크롤스킬
	static std::vector<Item> getScrolls();
};

extern std::vector<Item> g_ShopItemPool;   // 아이템 풀 선언

void RebuildShopItemPool(); // 아이템 풀 다시 채우는 함수