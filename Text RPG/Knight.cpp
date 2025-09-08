#include <iostream>
#include "Knight.h"
using namespace std;

Knight::Knight(string t_name) : Character(t_name)
{
	maxHealth = 200;
	health = maxHealth;
	attack = 15;

}

