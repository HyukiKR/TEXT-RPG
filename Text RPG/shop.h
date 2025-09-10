#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include "Item.h"
#include "Inventory.h"
#include "ItemFactory.h"
#include "Job.h"  // Job enum 추가
using namespace std;

// 전방 선언
class Character;

class Shop {
private:
    vector<Item> items_;

    void showBuyList() const;
    bool buyOnce(int& playerGold, Inventory& inv);
    bool sellOnce(int& playerGold, Inventory& inv);

public:
    Shop();

    void setStockForJob(Job job, int classCount = 2, int scrollCount = 2);
    void open(int& playerGold, Inventory& inv);

    // Character 객체를 받아서 직업 정보를 얻는 오버로드 버전
    void open(Character* player, Inventory& inv);
};