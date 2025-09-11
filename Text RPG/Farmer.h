#pragma once
#include "Character.h"

class Farmer : public Character {
public:
    Farmer(string t_name);
    void passiveSkill() override;
    void attackMassage() override;
};

