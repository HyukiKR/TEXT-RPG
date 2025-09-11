#pragma once
#include "Character.h"

class Alchemist : public Character {
public:
    Alchemist(string t_name);
    void passiveSkill() override;
    void attackMassage() override;
};
