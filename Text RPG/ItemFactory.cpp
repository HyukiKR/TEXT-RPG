#include "Item.h"
#include "ItemFactory.h"


std::vector<Item> ItemFactory::getAlchemistItems() {
	return{
		Item("Healing Elixir",
			 "연금술로 정제된 강력한 회복 물약",
			 "신비로운 엘릭서를 마셨습니다!",
			 ItemType::HEALTH_POTION, 15, 60, "연금술사"),

		Item("Explosive Potion",
			"폭발적인 힘을 일시적으로 부여하는 포션",
			"폭발 포션을 마셨습니다!",
			ItemType::ATTACK_BOOST, 25, 80, "연금술사"),

		Item("Mana Crystal",
			"마나가 응축된 강력한 회복력을 제공",
			"마나 에너지 방출!",
			ItemType::HEALTH_POTION, 25, 80, "연금술사")
	};
}

std::vector<Item> ItemFactory::getKnightItems() {
	return{
		Item("Scared Chalice",
			"축복이 깃든 신성한 성배",
			"성재에서 흘러나오는 신성한 물을 마셨습니다!",
			ItemType::HEALTH_POTION, 18, 55, "기사"),

		Item("Knight's Oath",
			"기사단의 맹세로 강화되는 신념의 힘",
			"신성한 힘이 검에 깃들었습니다!",
			ItemType::ATTACK_BOOST, 22, 11, "기사"),

		Item("Holy Water",
			"신전에서 축성된 거룩한 성수",
			"어둠의 기운이 사라지고 몸이 가벼워집니다!",
			ItemType::HEALTH_POTION, 12, 45, "기사")

	};
}

std::vector<Item> ItemFactory::getPirateItems() {
	return{
		Item("Rum Bottle",
			 "바다의 강한 럼",
			 "알코올이 상처를 소독했습니다!",
			 ItemType::HEALTH_POTION, 12, 45, "해적"),

		Item("Gunpowder Flask",
			 "화약의 분노로 전투력을 폭발시키는 물약",
			 "분노와 함께 화력이 급상승!",
			 ItemType::ATTACK_BOOST, 18, 13, "해적"),

		Item("Sea Salt",
			 "바닷바람에 말린 특별한 소금으로 체력 회복",
			 "바다의 생명력이 온 몸으로 퍼집니다!",
			 ItemType::HEALTH_POTION, 8, 35, "해적")
	};
}
std::vector<Item> ItemFactory::getFarmerItems() {
	return{
		 Item("Fresh Milk",
			 "자연 그대로의 신선한 농장 우유",
			 "신선한 우유가 깊숙이 스며들었습니다!",
			 ItemType::HEALTH_POTION, 8, 40, "농부"),

		Item("Sharpened Sickle",
			 "잘 갈아진 농기구로 일시적 공격력 증가",
			 "이 낫으로 몬스터도 베어버리겠어!",
			 ItemType::ATTACK_BOOST, 14, 9, "농부"),

		Item("Farm Bread",
			 "갓 구운 빵으로 든든한 회복",
			 "든든한 빵을 한 입 베어물었습니다!",
			 ItemType::HEALTH_POTION, 6, 30, "농부")
	};
}

std::vector<Item> ItemFactory::getAllItems() {
	std::vector<Item> allItems;

	//각 직업의 아이템들 모두 합치기
	auto alchemistItems = getAlchemistItems();
	auto knightItems = getKnightItems();
	auto pirateItems = getPirateItems();
	auto farmerItems = getFarmerItems();

	//모든 아이템을 하나의 벡터에 합치기
	allItems.insert(allItems.end(), alchemistItems.begin(), alchemistItems.end());
	allItems.insert(allItems.end(), knightItems.begin(), knightItems.end());
	allItems.insert(allItems.end(), pirateItems.begin(), pirateItems.end());
	allItems.insert(allItems.end(), farmerItems.begin(), farmerItems.end());

	return allItems;
}

//아이템 목록 가져오기
std::vector<Item> ItemFactory::getAllHealthPotions() {
	std::vector<Item> healthPotions;
	auto allItems = getAllItems();

	for (const auto& item : allItems) {
		if (item.getType() == ItemType::HEALTH_POTION) {
			healthPotions.push_back(item);
		}
	}

	return healthPotions;

}

//아이템 목록 가져오기
std::vector<Item> ItemFactory::getAllAttackBoosts() {
	std::vector<Item> attackBoosts;
	auto allItems = getAllItems();

	for (const auto& item : allItems) {
		if (item.getType() == ItemType::ATTACK_BOOST) {
			attackBoosts.push_back(item);
		}
	}

	return attackBoosts;
}

//스킬스크롤
std::vector<Item> ItemFactory::getScrolls()
{
	return {
		Item("Fireball Scroll",
			"불덩이를 발사 마법 스크롤",
			"거대한 불덩이가 적을 덮쳤습니다!",
			ItemType::SCROLL, 50, 40, "전체 직업"),

		Item("Healing Scroll",
			"즉시 체력 회복 마법 스크롤",
			"상처가 치유됩니다!",
			ItemType::SCROLL, 30, 50, "전체 직업"),

		Item("Explosive Bullet Scroll",
			"적에게 범위 피해를 입히는 폭발탄",
			"주변 적들이 폭발에 휩싸였습니다!",
			ItemType::SCROLL, 50, 40, "전체 직업"),

		Item("Piercing shot Scroll",
			"적 방어를 무시하는 강력한 관통탄",
			"적 방어를 뚫고 강력한 피해를 입혔습니다!",
			ItemType::SCROLL, 60, 50, "전체 직업"),

		Item("Smoke Bomb Scroll",
			"적 공격력 감소 및 회피율 증가",
			"시야가 가려지고 적의 공격력이 감소합니다!",
			ItemType::SCROLL, 35, 20, "전체 직업")

	};
}
