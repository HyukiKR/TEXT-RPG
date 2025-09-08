#include <iostream>
#include "Pirate.h"
using namespace std;

Pirate::Pirate(string t_name) : Character(t_name)
{
	maxHealth = 220;
	health = maxHealth;
	attack = 10;

}

