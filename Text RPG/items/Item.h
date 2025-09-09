#ifndef ITEM_H
#define ITEM_H

#include <string>

class Character; //전방선언

enum class ItemType {
	HEALTH_POTION, // 체력 회복
	ATTACK_BOOST	// 공격력 강화
};

class Item{
private:
	std::string name_;
	std::string description_; //간단한 설명?
	std::string flavorText_; //사용시 출력되는 텍스트
	ItemType type_;
	int price_;
	int effect_value_;
	std::string associatedClass_; //어떤 직업의 아이템인가

public:
	//생성자
	Item(const std::string& name, const std::string& description, const std::string& flavorText, ItemType type, int price, int effect_value, const std::string& associatedClass);

	//Getter 함수
	std::string getName() const { return name_; }
	std::string getDescription() const { return description_; }
	std::string getflavorText() const { return flavorText_; }
	ItemType getType() const { return type_; }
	int getPrice() const { return price_; }
	int geteffect_value() const { return effect_value_; }
	int getSellPrice() const { return static_cast<int>(price_ * 0.6); }

	//아이템 사용 함수 (효과 메시지)
	void use(Character* character) const;

	//아이템 정보 출력
	void displayInfo() const;
	};

#endif 