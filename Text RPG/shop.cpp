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

bool Shop::buyOnce(int& playerGold, Inventory& inv) {
    UI ui;
    system("cls");
    if (inv.isFull()) {
        cout << "인벤토리가 가득 차서 구매할 수 없습니다.\n";
        return false;
    }
    vector<Item*> itemPtrs;

    for (auto& obj : items_)
    {
        itemPtrs.push_back(&obj);
    }

    int sel = ui.buyDisplay(itemPtrs);

    if (sel == 4) 
        return false;

    if (items_.size() != 0)
    {
        const Item& it = items_[sel];

        if (playerGold < it.getPrice()) {
            cout << endl << endl << "골드가 부족합니다.\n";

            system("pause");
            return false;
        }

        playerGold -= it.getPrice();
        inv.addItem(it);
        cout << endl << endl << it.getName() << " 구매 완료! (남은 골드: " << playerGold << ")\n";
        system("pause");
        return true;
    }
    else
    {
        cout << endl << endl << "재고가 없습니다." << endl;
        system("pause");
        return false;
    }
}

bool Shop::sellOnce(int& playerGold, Inventory& inv) {
    UI ui;
    system("cls");

    vector<const Item*> itemPtrs;

    for (int i = 0; i < 5; i++)
    {
        const Item* itemPtr = inv.getItem(i);
        itemPtrs.push_back(itemPtr);
    }

    int sel = ui.sellDisplay(itemPtrs);

    if (sel == 5) return false;

    const Item* it = inv.getItem(sel);

    if (it == nullptr)
    {
        cout << endl << endl << "비어있습니다." << endl;
        system("pause");
        return false;
    }
    else
    {
        int sellPrice = (int)round(it->getPrice() * 0.6);
        playerGold += sellPrice;
        inv.eraseAt(sel);

        cout << it->getName() << " 판매! +" << sellPrice
            << "G (현재 골드: " << playerGold << ")\n";

        system("pause");

        return true;
    }
}

void Shop::open(int& playerGold, Inventory& inv) {
    UI ui;

    while (true) 
    {
        int sel = ui.ShopMenuDisplay();

        switch (sel)
        {
        case 1:
            buyOnce(playerGold, inv);
            break;
        case 2:
            sellOnce(playerGold, inv);
            break;
        case 3:
            inv.showWithSlots();
            break;
        case 4:
            return;
        }
    }
}