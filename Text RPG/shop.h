#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include "Item.h"
#include "Inventory.h"
#include "ItemFactory.h"
#include "Character.h" 
using namespace std;

class Shop {
private:
    vector<Item> items_;

    void showBuyList() const;
    bool buyOnce(Character& player);
    bool sellOnce(Character& player);

public:
    Shop();

    void setStockForJob(Job job, int classCount = 2, int scrollCount = 2);
    void open(Character& player);
};
