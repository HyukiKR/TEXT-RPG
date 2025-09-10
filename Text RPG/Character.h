#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
using namespace std;

class Character {
protected:
	static Character* instance;
	string name;
	string job_name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int gold;
	//vector<Item*> inventory;

	Character(string t_name);
	~Character();

	int randNum(int a = 0, int b = 0);

public:

	//복사 생성자와 대입 연산자 삭제
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

	//정적 메소드: 유일한 캐릭터 인스턴트를 반환
	static Character* getInstance(const string name = "", int job = 0);

	void displayStatus() const;
	void levelUp();
	void useItem(const int index);
	virtual void passiveSkill() = 0;
	void healHealth(const int heal);
	void boostAttack(const int boost);
	virtual void attackMassage() = 0;

	//get
	string getName() const;
	string getJobName() const;
	int getLevel() const;
	int getHealth() const;
	int getAttack() const;
	int getExperience() const;
	int getGold() const;


	//set
	void setExperience(int exp);
	void setGold(int amount);
	void takeDamage(int damage);


};

#endif // !CHARACTER_H