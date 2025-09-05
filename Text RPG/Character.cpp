#include "Character.h"
#include <iostream>

//�����ڿ� �Ҹ��� ����
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

//ĳ���� ����â ���÷���
void Character::displayStatus() const
{
	cout << endl <<  "�̸�: " << name << endl;
	cout << "����: " << level << endl;
	cout << "ü��: " << health << "/" << maxHealth << endl;
	cout << "���ݷ�: " << attack << endl;
	cout << "����ġ: " << experience << endl;
	cout << "���: " << gold << endl;
}

//������ �޼ҵ�
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
		cout << "�ִ� ������ 10�� �����߽��ϴ�." << endl;
}

//������ ��� �޼ҵ�
void Character::useItem(const int index)
{
	//������ ��� �ý���
}

//set �Լ�
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

//get �Լ�
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