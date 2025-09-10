#pragma once

#include <vector>

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
};

