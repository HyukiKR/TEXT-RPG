#include "Inventory.h"

void Inventory::addItem(const Item& item) {
    if ((int)items_.size() >= MAX_SIZE) {
        cout << "인벤토리가 가득 찼습니다! (최대 " << MAX_SIZE << "개)\n";
        return;
    }
    items_.push_back(item);
}

void Inventory::eraseAt(int idx) {
    if (idx < 0 || idx >= (int)items_.size()) return;
    items_.erase(items_.begin() + idx);
}

int Inventory::size() const {
    return (int)items_.size();
}

const Item* Inventory::getItem(int idx) const {
    if (idx < 0 || idx >= (int)items_.size()) return nullptr;
    return &items_[idx];
}

bool Inventory::isFull() const {
    return (int)items_.size() >= 5;
}

void Inventory::showItemsSimple() const {
    cout << "[인벤토리] (" << size() << "/" << MAX_SIZE << ")\n";
    if (items_.empty()) {
        cout << "인벤토리가 비어 있습니다.\n";
        return;
    }
    for (int i = 0; i < (int)items_.size(); ++i) {
        cout << (i + 1) << ") " << items_[i].getName() << "\n";
    }
}

void Inventory::showWithSlots() const {
    cout << "[인벤토리] (" << size() << "/" << MAX_SIZE << ")\n";
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (i < (int)items_.size()) {
            cout << (i + 1) << ") " << items_[i].getName() << "\n";
        }
        else {
            cout << (i + 1) << ") [빈칸]\n";
        }
    }
}