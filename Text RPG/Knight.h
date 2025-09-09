#pragma once
#include "Character.h"

class Knight : public Character {
public:
    Knight(string t_name);
    void passiveSkill() override;
};
