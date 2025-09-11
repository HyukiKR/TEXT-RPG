#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Item.h"
#include "Character.h" 
#include <limits>

using namespace std;

class Inventory {
private:
    vector<Item> items_;
    const int MAX_SIZE = 5;

public:
    void addItem(const Item& item);
    void eraseAt(int idx);

    int  size() const;
    const Item* getItem(int idx) const;

    bool isFull() const;
    int  capacity() const { return MAX_SIZE; }

    void showItemsSimple() const;  // 아이템 이름만 표시
    void showWithSlots() const;    // 5칸 고정 (빈칸도 표시)
};