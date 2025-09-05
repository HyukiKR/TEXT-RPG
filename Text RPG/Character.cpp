#include "Character.h"
#include <iostream>

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
}
Character::~Character()
{
	delete instance;
}

//캐릭터 상태창 디스플레이
void Character::displayStatus() const
{
	cout << endl <<  "이름: " << name << endl;
	cout << "레벨: " << level << endl;
	cout << "체력: " << health << "/" << maxHealth << endl;
	cout << "공격력: " << attack << endl;
	cout << "경험치: " << experience << endl;
	cout << "골드: " << gold << endl;
}

//레벨업 메소드
void Character::levelUp()
{
	if (level <= 10)
	{
		level++;
		experience -= 100;		
		maxHealth += level * 20;
		health = maxHealth;
		attack += level * 5;
	}
	else
		cout << "최대 레벨인 10에 도달했습니다." << endl;
}

//아이템 사용 메소드
void Character::useItem(const int index)
{
	//아이템 사용 시스템
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
	experience += exp;
	if (experience >= 100)
	{
		levelUp();
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

//get 함수
string Character::getName() const
{
	return name;
}

int Character::getLevel() const
{
	return level;
}

int Character::getHealth() const
{
	return health;
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