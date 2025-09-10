#include <iostream>
#include "Alchemist.h"
using namespace std;

Alchemist::Alchemist(string t_name) : Character(t_name)
{
	maxHealth = 150;
	health = maxHealth;
	attack = 13;
	
}

