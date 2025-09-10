#include "GameManager.h"
#include "GameLogger.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// ���� ȭ�鿡 ��µǴ� ���÷���
void displayBattleChoice()
{
	cout << endl << "---------------------------" << endl;
	cout << "���� �ý���" << endl;
	cout << "1. ����" << endl;
	cout << "2. �κ��丮 Ȯ��" << endl;
	cout << "3. ���� ����" << endl;
	cout << "---------------------------" << endl << endl;
	cout << "����: ";
}

Monster* GameManager::generateMonster(int level)
{
	int ran = randNum(0, 3);

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

// ���� ���� ���� �޼ҵ�
vector<Monster*> GameManager::generateMultipleMonsters(int playerLevel)
{
	vector<Monster*> monsters;
	int monsterCount = randNum(2, 4);  // 2~4���� ����

	cout << "���� ���Ͱ� ��Ÿ����! (�� " << monsterCount << "����)" << endl;

	for (int i = 0; i < monsterCount; i++)
	{
		// �÷��̾� ���� -1 ~ �÷��̾� ���� ������ ���� ����
		int monsterLevel = max(1, playerLevel - randNum(0, 1));
		Monster* monster = generateMonster(monsterLevel);
		monsters.push_back(monster);
		cout << (i + 1) << ". " << monster->getName()
			<< " (ü��: " << monster->getHealth()
			<< ", ���ݷ�: " << monster->getAttack() << ")" << endl;
	}

	return monsters;
}

// ���� ���� ����
void GameManager::multiBattle(Character* Player, vector<Monster*>& monsters)
{
	GameLogger* logger = GameLogger::getInstance();
	int totalExp = 0;
	int defeatedCount = 0;

	cout << endl << "=== ���� ���� ���� ����! ===" << endl;

	while (!monsters.empty() && Player->getHealth() > 0)
	{
		// ���� ���� ���� ǥ��
		cout << endl << "--- ���� ���� ---" << endl;
		for (int i = 0; i < monsters.size(); i++)
		{
			cout << (i + 1) << ". " << monsters[i]->getName()
				<< " (ü��: " << monsters[i]->getHealth() << ")" << endl;
		}

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
		{
			// ������ ���� ����
			cout << "������ ���� ��ȣ�� �����ϼ���: ";
			int targetIndex;
			cin >> targetIndex;

			if (targetIndex < 1 || targetIndex > monsters.size())
			{
				cout << "�߸��� �����Դϴ�." << endl;
				continue;
			}

			Monster* target = monsters[targetIndex - 1];

			// �÷��̾� ����
			cout << Player->getName() << "��(��) " << target->getName() << "��(��) �����մϴ�! ";
			target->takeDamage(Player->getAttack());

			if (target->getHealth() <= 0)
			{
				cout << target->getName() << " óġ!" << endl;
				logger->logBattle(target->getName(), true);  // �α� �߰�
				totalExp += 50;  // ���ʹ� 50 ����ġ
				defeatedCount++;

				delete target;
				monsters.erase(monsters.begin() + targetIndex - 1);

				if (monsters.empty())
				{
					cout << endl << "��� ���͸� óġ�߽��ϴ�!" << endl;
					cout << "�� " << defeatedCount << "���� óġ!" << endl;
					reward(Player, totalExp);  // �� ����ġ �ѹ��� ����
					return;
				}
			}
			else
			{
				cout << target->getName() << " ü��: " << target->getHealth() << endl;
			}

			// ���� ���͵��� �ݰ�
			cout << endl << "--- ���͵��� �ݰ�! ---" << endl;
			for (Monster* monster : monsters)
			{
				cout << monster->getName() << "��(��) " << Player->getName() << "��(��) �����մϴ�! ";
				int tempHealth = Player->getHealth();
				Player->takeDamage(monster->getAttack());
				cout << "������: " << monster->getAttack()
					<< " (ü��: " << tempHealth << " -> " << Player->getHealth() << ")" << endl;

				if (Player->getHealth() <= 0)
				{
					cout << Player->getName() << "�� ���������ϴ�. ���� ����!" << endl;
					logger->logBattle("��������", false);  // �α� �߰�

					// �޸� ����
					for (Monster* m : monsters)
					{
						delete m;
					}
					monsters.clear();

					exit(0);
				}
			}
			break;
		}

		case 2:
		{
			Inventory inv;
			inv.showItemsSimple();
			break;
		}

		case 3:
		{
			cout << "������ �����մϴ�." << endl;

			// �޸� ����
			for (Monster* m : monsters)
			{
				delete m;
			}
			monsters.clear();

			exit(0);
			break;		
		}			

		default:
			cout << "�߸��� �����Դϴ�. 1 �Ǵ� 2�� �������ּ���." << endl;
			break;
		}


	}
}

// ���� ���� ���� (������ battle �޼ҵ�)
void GameManager::battle(Character* Player)
{
	GameLogger* logger = GameLogger::getInstance();

	// 30% Ȯ���� ���� ���� ����
	int battleType = randNum(1, 10);

	if (battleType <= 3)  // 30% Ȯ��
	{
		cout << "!! ���: �ټ��� ���� ���� !!" << endl;
		vector<Monster*> monsters = generateMultipleMonsters(Player->getLevel());
		multiBattle(Player, monsters);
	}
	else  // 70% Ȯ���� ���� ���� ����
	{
		int tempHealth;
		Monster* monster = generateMonster(Player->getLevel());
		cout << "�߻� " << monster->getName() << " ����! ü��: " << monster->getHealth()
			<< ", ���ݷ�: " << monster->getAttack() << endl;

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
			{	// �÷��̾� ����
				cout << Player->getName() << "��(��) " << monster->getName() << "��(��) �����մϴ�! ";
				monster->takeDamage(Player->getAttack());

				if (monster->getHealth() <= 0)
				{
					cout << monster->getName() << " óġ!" << endl;
					logger->logBattle(monster->getName(), true);  // �α� �߰�
					delete monster;
					reward(Player, 50);
					return;
				}
				else
				{
					cout << monster->getName() << " ü��: " << monster->getHealth() << endl;
				}

				// ���� ����
				cout << monster->getName() << "��(��) " << Player->getName() << "��(��) �����մϴ�! ";
				tempHealth = Player->getHealth();
				Player->takeDamage(monster->getAttack());

				if (Player->getHealth() <= 0)
				{
					cout << Player->getName() << " ü��: " << tempHealth << " -> " << Player->getHealth() << endl;
					cout << Player->getName() << "�� ���������ϴ�. ���� ����!" << endl;
					logger->logBattle(monster->getName(), false);  // �α� �߰�
					delete monster;
					exit(0);
				}
				else
				{
					cout << Player->getName() << " ü��: " << Player->getHealth() << endl;
				}
				break;
			}

			}
				
			case 2:
			{
				Inventory inv;
				inv.showItemsSimple();
				break;
			}

			case 3:
			{
				cout << "������ �����մϴ�." << endl;
				delete monster;
				exit(0);
				break;
			}
			default:
				cout << "�߸��� �����Դϴ�. 1 �Ǵ� 2�� �������ּ���." << endl;
				break;				
			}
		}
	}
}

void GameManager::displayInventory(Character* Player)
{
	// �κ��丮 ���÷��� �ý���
	cout << "=== �κ��丮 ===" << endl;
	cout << "��� �̱���" << endl;
}

void GameManager::reward(Character* Player, int exp)
{
	GameLogger* logger = GameLogger::getInstance();
	int ran = randNum(20, 30);

	// ����ġ �� ��� ���� �ý���
	Player->setExperience(exp);
	Player->setGold(ran);

	// �α� ���
	logger->logExpEarned(exp);
	logger->logGoldEarned(ran);

	cout << "���� �¸� : ����ġ " << exp << " ȹ��, ���: " << ran << "G ȹ��!" << endl;

	// ������ ȹ�� Ȯ�� 30%
	ran = randNum(1, 10);
	if (ran >= 1 && ran <= 3) {
		cout << "������ ȹ��!" << endl;
		logger->logItemFound("���� ������");
	}
	else
		cout << "������ ȹ�� ����!" << endl;
}

int GameManager::randNum(int min, int max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(min, max);

	return dist(gen);
}