#include "Shop.h"
#include "Character.h"
#include <ctime> // 초마다 시드를 변경하여 매번 상점마다 다른 랜덤한 결과가 나오기위해 필요하다네요...

Shop::Shop() {
    
}
void Shop::setStockForJob(Job job, int classCount, int scrollCount) {
    items_.clear();

    // 아이템 풀
    vector<Item> classPool;
    switch (job) {
    case Job::Alchemist:
        classPool = ItemFactory::getAlchemistItems();
        break;
    case Job::Knight:
        classPool = ItemFactory::getKnightItems();
        break;
    case Job::Pirate:
        classPool = ItemFactory::getPirateItems();
        break;
    case Job::Farmer:
        classPool = ItemFactory::getFarmerItems();
        break;
    }

    // 스크롤 풀
    vector<Item> scrollPool = ItemFactory::getScrolls();

    //  랜덤으로 아이템이 나오게 하는 함수
    unsigned seed = (unsigned)time(nullptr);
    shuffle(classPool.begin(), classPool.end(), default_random_engine(seed));
    shuffle(scrollPool.begin(), scrollPool.end(), default_random_engine(seed + 1));

    int takeClass = min(classCount, (int)classPool.size());
    int takeScroll = min(scrollCount, (int)scrollPool.size());

    for (int i = 0; i < takeClass; ++i) items_.push_back(classPool[i]);
    for (int i = 0; i < takeScroll; ++i) items_.push_back(scrollPool[i]);

    // (옵션) 총 4개가 안 채워지면 가능한 범위에서 보충
    int target = classCount + scrollCount;
    if ((int)items_.size() < target) {
        vector<Item> refill;
        for (int i = takeClass; i < (int)classPool.size(); ++i) refill.push_back(classPool[i]);
        for (int i = takeScroll; i < (int)scrollPool.size(); ++i) refill.push_back(scrollPool[i]);
        shuffle(refill.begin(), refill.end(), default_random_engine(seed + 2));
        int need = target - (int)items_.size();
        for (int i = 0; i < need && i < (int)refill.size(); ++i) items_.push_back(refill[i]);
    }
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