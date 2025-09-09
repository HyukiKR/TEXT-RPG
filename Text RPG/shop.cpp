#include "Shop.h"

Shop::Shop() {
    // 도연님 Item 준비되면 여기서 판매 목록 추가
    // items_.push_back(Item("Health Potion (+50 HP)", 10, 50, 0));
    // items_.push_back(Item("Attack Boost (+10 ATK)", 15, 0, 10));
}

void Shop::showBuyList() const {
    cout << "[구매]\n";
    for (int i = 0; i < (int)items_.size(); ++i) {
        cout << (i + 1) << ") "
            << items_[i].getName()
            << " - " << items_[i].getPrice() << "G\n";
    }
    cout << "0) 뒤로\n";
}

bool Shop::buyOnce(int& playerGold, Inventory& inv) {
    if (inv.isFull()) {
        cout << "인벤토리가 가득 차서 구매할 수 없습니다.\n";
        return false;
    }

    showBuyList();
    cout << "선택: ";
    int sel; cin >> sel;
    if (sel == 0) return false;

    int idx = sel - 1;
    if (idx < 0 || idx >= (int)items_.size()) {
        cout << "잘못된 선택입니다.\n";
        return false;
    }

    const Item& it = items_[idx];
    if (playerGold < it.getPrice()) {
        cout << "골드가 부족합니다.\n";
        return false;
    }

    playerGold -= it.getPrice();
    inv.addItem(it);
    cout << it.getName() << " 구매 완료! (남은 골드: " << playerGold << ")\n";
    return true;
}

bool Shop::sellOnce(int& playerGold, Inventory& inv) {
    inv.showItemsSimple();
    cout << "0) 뒤로\n판매할 번호: ";
    int sel; cin >> sel;
    if (sel == 0) return false;

    int idx = sel - 1;
    if (idx < 0 || idx >= inv.size()) {
        cout << "잘못된 선택입니다.\n";
        return false;
    }

    const Item* it = inv.getItem(idx);
    if (!it) return false;

    int sellPrice = (int)round(it->getPrice() * 0.6);
    playerGold += sellPrice;
    inv.eraseAt(idx);

    cout << it->getName() << " 판매! +" << sellPrice
        << "G (현재 골드: " << playerGold << ")\n";
    return true;
}

void Shop::open(int& playerGold, Inventory& inv) {
    while (true) {
        cout << "\n[상점] 골드: " << playerGold << "\n"
            << "1) 구매\n"
            << "2) 판매\n"
            << "3) 인벤토리 보기\n"
            << "0) 나가기\n"
            << "선택: ";
        int sel; cin >> sel;
        if (sel == 0) break;
        if (sel == 1) { buyOnce(playerGold, inv); }
        else if (sel == 2) { sellOnce(playerGold, inv); }
        else if (sel == 3) { inv.showWithSlots(); }
        else { cout << "잘못된 선택입니다.\n"; }
    }
}
