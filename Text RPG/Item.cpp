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
		//+스킬스크롤 추가
	case ItemType::SCROLL:
		cout << name_ << "스크롤을 펼쳤습니다!" << endl;
		if (name_ == "Fireball Scroll") {
			cout << "불덩이가 날아가 적을 태웁니다! (데미지 " << effect_value_ << ")" << endl;
		}
		else if (name_ == "Healing Scroll") {
			character->healHealth(effect_value_);
			cout << "치유의 기운이 몸을 감쌉니다! 체력++ " << effect_value_ << endl;
		}
		// 몬스터 클래스에 호출하실건지..
		else if (name_ == "Explosive Bullet Scroll") {
			cout << "폭발탄이 주변 적들에게 퍼집니다! (데미지 " << effect_value_ << ")" << endl;
		}
		else if (name_ == "Explosive Bullet Scroll") {
			cout << "관통탄이 적 방어를 무시하고 명중했습니다! (데미지 " << effect_value_ << ")" << endl;
		}
		else if (name_ == "Smoke Bomb Scroll") {
			cout << "연막탄으로 시야가 가려지고, 적의 공격력이 감소합니다!" << endl;
		}
		else {
			cout << "알 수 없는 스크롤입니다." << endl;
		}
		break;
	default:
		cout << "이 아이템은 사용할 수 없습니다! " << endl;
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
	case ItemType::SCROLL:
		if (name_ == "Fireball Scroll") {
			cout << "적에게" << effect_value_ << "데미지";
		}
		else if (name_ == "Healing Scroll") {
			cout << "체력 +" << effect_value_ << "회복";
		}
		else {
			cout << "특별한 효과 (데미지/회복: " << effect_value_ << ")";
		}
		break;
	default:
		cout << "알 수 없는 효과";
		break;
	}
	cout << endl;
	cout << "설명: " << flavorText_ << endl;
	cout << "\n==============================================================" << endl;
}

