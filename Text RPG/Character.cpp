#include "Character.h"
#include "GameLogger.h"
#include "Knight.h"
#include "Alchemist.h"
#include "Pirate.h"
#include "Farmer.h"
#include <iostream>
#include <random>
#include "inventory.h"

//생성자와 소멸자 정의
Character::Character(string t_name)
{
	name = t_name;
	level = 1;
	maxHealth = 200;
	health = maxHealth;
	attack = 10;
	experience = 0;
	gold = 0;
	scroll = 0;
	attackBoost = 0;
	inventory = new Inventory();
}
Character::~Character()
{
	delete instance;
	delete inventory;
}

//정적 메소드: 유일한 캐릭터 인스턴트를 반환
Character* Character::getInstance(const string name, int job)
{
	if (instance == nullptr && !name.empty()) {
		job == 1 ? instance = new Knight(name) :
			job == 2 ? instance = new Alchemist(name) :
			job == 3 ? instance = new Pirate(name) :
			job == 4 ? instance = new Farmer(name) :
			instance = new Knight(name);
	}
	return instance;
}

//캐릭터 상태창 디스플레이
void Character::displayStatus() const
{
	system("cls");
	cout << endl << "이름: " << name << endl;
	cout << "레벨: " << level << endl;
	cout << "체력: " << health << "/" << maxHealth << endl;
	cout << "공격력: " << attack << endl;
	cout << "경험치: " << experience << endl;
	cout << "골드: " << gold << endl;

	system("pause");
}

//레벨업 메소드
void Character::levelUp()
{
	const int MAX_LEVEL = 10;

	if (level < MAX_LEVEL)
	{
		level++;
		experience -= 100;
		maxHealth += level * 20;
		health = maxHealth;
		attack += level * 5;
		cout << "레벨업! 현재 레벨: " << level << endl;
		GameLogger::getInstance()->logLevelUp(level);  // 로그 추가
	}
	else
	{
		cout << "최대 레벨인 " << MAX_LEVEL << "에 도달했습니다." << endl;
	}
}

//랜덤 숫자 반환 함수
int Character::randNum(int a, int b)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());  // Mersenne Twister 엔진 사용
	std::uniform_int_distribution<> distrib(a, b);
	return distrib(gen);
}


//아이템 사용 메소드
void Character::useItem(const int index)
{
	//아이템 사용 시스템
}

//체력 회복
void Character::healHealth(const int heal)
{
	health += heal;
	if (health > maxHealth)
	{
		health = maxHealth;
	}
}

//추가 공격력 
void Character::boostAttack(const int boost)
{
	attackBoost = boost;
}

//set 함수
void Character::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
	{
		health = 0;
	}
}

void Character::setExperience(int exp)
{
	const int MAX_LEVEL = 10;

	// 최대 레벨에서는 경험치를 더 이상 받지 않음
	if (level >= MAX_LEVEL)
	{
		cout << "최대 레벨이므로 경험치를 획득할 수 없습니다." << endl;
		return;
	}

	experience += exp;

	// 경험치가 100 이상이면 레벨업 (연속 레벨업 가능) && 연산자로 다중 조건 처리
	while (experience >= 100 && level < MAX_LEVEL)
	{
		levelUp();  // levelUp() 내부에서 experience -= 100 처리됨
	}
}

void Character::setGold(int amount)
{
	gold += amount;
	if (gold < 0)
	{
		gold = 0;
	}
}

void Character::setScroll(int value)
{
	scroll = value;
}

//get 함수
string Character::getName() const
{
	return name;
}

string Character::getJobName() const
{
	return job_name;
}

int Character::getLevel() const
{
	return level;
}

int Character::getHealth() const
{
	return health;
}

int Character::getMaxHealth() const
{
	return maxHealth;
}


int Character::getAttack() const
{
	return attack;
}

int Character::getExperience() const
{
	return experience;
}

int Character::getGold() const
{
	return gold;
}

Inventory& Character::getInventory() {
	return *inventory;   // 포인터를 참조로 변환
}

const Inventory& Character::getInventory() const {
	return *inventory;
}

int Character::getScroll() const
{
	return scroll;
}

int Character::getAttackBoost() const
{
	return attackBoost;
}

//아이템 사용
void Character::useItemFromInventory() {
	if (inventory->size() == 0) {
		cout << "인벤토리가 비어있습니다!" << endl;
		return;
	}

	cout << "어떤 아이템을 사용하시겠습니까?" << endl;
	cout << "======================" << endl;
	inventory->showItemsSimple();
	cout << "0) 지금은 사용하지 않는다 " << endl;
	cout << "======================" << endl;
	cout << "사용할 아이템 번호: ";
	int sel;
	cin >> sel;

	if (sel == 0) return; // 뒤로
	int idx = sel - 1;

	if (idx < 0 || idx >= inventory->size()) {
		cout << "잘못된 선택입니다." << endl;
		return;
	}

	const Item* it = inventory->getItem(idx);
	if (!it) {
		cout << "존재하지 않는 아이템입니다." << endl;
		return;
	}

	// 아이템 효과 적용
	it->use(this);

	// 소모품이므로 인벤토리에서 제거
	inventory->eraseAt(idx);
	
}
