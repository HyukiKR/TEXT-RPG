#include <iostream>
#include "Farmer.h"
using namespace std;

Farmer::Farmer(string t_name) : Character(t_name)
{
	maxHealth = 180;
	health = maxHealth;
	attack = 8;

}

