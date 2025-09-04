#include "GameManager.h"
#include <iostream>
#include <random>

// ���� ȭ�鿡 ��µǴ� ������
void displayBattleChoice()
{
	cout <<  endl <<  "---------------------------" << endl;
	cout << "���� �ý���" << endl;
	cout << "1. ����" << endl;
	cout << "2. ���� ����" << endl;
	cout << "---------------------------" << endl << endl;
	cout << "����: ";
}

Monster* GameManager::generateMonster(int level)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, 3);

	int ran = dist(gen);

	switch (ran)
	{
	case 0:
		return new Goblin(level);
	case 1:
		return new Troll(level);
	case 2:
		return new Orc(level);
	case 3:
		return new Slime(level);
	default:
		return nullptr;
	}
}

void GameManager::battle(Character* Player)
{
	int tempHealth;
	Monster* monster = generateMonster(Player->getLevel());
	cout << "���� " << monster->getName() << " ����! ü��: " << monster->getHealth() << ", ���ݷ�: " << monster->getAttack() << endl;
	while (true)
	{
		displayBattleChoice();
		int choice;
		cin >> choice;
		if (cin.fail()) {
			cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���." << endl << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}
		switch (choice)
		{
		case 1:
			//�÷��̾� ����
			cout << Player->getName() << "��(��) " << monster->getName() << "��(��) �����մϴ�! ";
			monster->takeDamage(Player->getAttack());
			if (monster->getHealth() <= 0)
			{
				cout << monster->getName() << "óġ!" << endl;
				delete monster;
				return;
			}
			else
			{
				cout << monster->getName() << " ü��: " << monster->getHealth() << endl;
			}
			//���� ����
			cout << monster->getName() << "��(��) " << Player->getName() << "��(��) �����մϴ�! ";
			tempHealth = Player->getHealth();
			Player->takeDamage(monster->getAttack());
			if (Player->getHealth() <= 0)
			{
				cout << Player->getName() << "ü��: " << tempHealth << " -> " << Player->getHealth() << endl;
				cout << Player->getName() << "�� ����߽��ϴ�. ���� ����!" << endl;
				exit(0);
			}
			else
			{
				cout << Player->getName() << " ü��: " << Player->getHealth() << endl;
			}
			break;
		case 2:
			cout << "������ �����մϴ�." << endl;
			exit(0);
			break;
		}
	}
}

void GameManager::displayInventory(Character* Player)
{
	//�κ��丮 ���÷��� �ý���
}