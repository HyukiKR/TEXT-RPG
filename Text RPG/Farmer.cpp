#include <iostream>
#include "Farmer.h"
using namespace std;

Farmer::Farmer(string t_name) : Character(t_name)
{
	maxHealth = 180;
	health = maxHealth;
	attack = 8;
	job_name = "³óºÎ";
}

void Farmer::passiveSkill() {} // ³óºÎ´Â ¼º½ÇÇÏ´Ù...

void Farmer::attackMassage()  // ³óºÎÀÇ °ø°Ý
{
	int category = randNum(0, 1);

	if (category == 0)
	{
		cout << "È£¹Ì·Î Âï¾î¹ö¸®ÀÚ! " << endl;
	}
	else
	{
		cout << "±ªÀÌ¸¦ ÈÖµÎ¸£ÀÚ! " << endl;
	}
}

