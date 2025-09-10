#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include "Item.h"
#include "Inventory.h"
using namespace std;

class Shop {
private:
    vector<Item> items_;

    void showBuyList() const;
    bool buyOnce(int& playerGold, Inventory& inv);
    bool sellOnce(int& playerGold, Inventory& inv);

public:
    Shop();
    void open(int& playerGold, Inventory& inv);
};