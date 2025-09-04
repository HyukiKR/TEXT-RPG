#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
using namespace std;

class Character {
private:
	static Character* instance;
	string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int gold;
	//vector<Item*> inventory;

	Character(string t_name);
	~Character();
public:

	//복사 생성자와 대입 연산자 삭제
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

	//정적 메소드: 유일한 캐릭터 인스턴트를 반환
	static Character* getInstance(const string name = "")
	{
		if (instance == nullptr && !name.empty()) {
			instance = new Character(name);
		}
		return instance;
	}

	void displayStatus() const;
	void levelUp();
	void useItem(const int index);
	
	//get
	string getName() const;
	int getLevel() const;
	int getHealth() const;
	int getAttack() const;
	int getExperience() const;
	int getGold() const;

	//set
	void takeDamage(int damage);
};

#endif // !CHARACTER_H