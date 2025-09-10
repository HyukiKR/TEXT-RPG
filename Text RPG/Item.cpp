#include "Item.h"
#include "Character.h"
#include <iostream>

using namespace std;

Item::Item(const string& name, const string& description, const string& flavorText, ItemType type, int price, int effect_value, const string& associatedClass)
	: name_(name), description_(description), flavorText_(flavorText), type_(type), price_(price), effect_value_(effect_value), associatedClass_(associatedClass) {
}

void Item::use(Character* character) const {
	cout << "\n" << flavorText_ << endl;

	switch (type_)
	{
	case ItemType::HEALTH_POTION:
		character->healHealth(effect_value_); // 캐릭터 함수에 health 올리는 함수 구현해주세요!
		cout << "체력이 " << effect_value_ << "회복되었습니다!" << endl;
		break;
	case ItemType::ATTACK_BOOST:
		character->boostAttack(effect_value_); //캐릭터 함수에 Attack 올리는 함수 구현해주세요!
		cout << "공격력이 " << effect_value_ << "증가했습니다!" << endl;
		break;
	}
}

void Item::displayInfo()const {
	cout << " " << name_ << " - 가격: " << price_ << " Gold";
	cout << "(판매: " << getSellPrice() << " Gold)" << endl;
	cout << " " << description_ << endl;
	cout << "\n==============================================================" << endl;
	cout << "직업: " << associatedClass_ << endl;
	cout << "효과: ";
	switch (type_) {
	case ItemType::HEALTH_POTION:
		cout << "체력 +" << effect_value_ << " 회복";
		break;
	case ItemType::ATTACK_BOOST:
		cout << "공격력 +" << effect_value_ << " 증가";
		break;
	};
	cout << endl;
	cout << "설명: " << flavorText_ << endl;
	cout << "\n==============================================================" << endl;
}

