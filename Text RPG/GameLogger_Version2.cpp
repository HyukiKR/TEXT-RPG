#include "GameLogger.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <windows.h>

GameLogger* GameLogger::instance = nullptr;

GameLogger::GameLogger() {
    totalGoldEarned = 0;
    totalGoldSpent = 0;
    totalExpEarned = 0;
    totalItemsFound = 0;
    totalItemsBought = 0;
    totalItemsSold = 0;
    sessionStartTime = getCurrentTime();
}

GameLogger* GameLogger::getInstance() {
    if (instance == nullptr) {
        instance = new GameLogger();
    }
    return instance;
}

string GameLogger::getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') 
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    return ss.str();
}

void GameLogger::logBattle(const string& monsterName, bool victory) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "BATTLE";
    
    if (victory) {
        entry.message = monsterName + " 처치!";
        monsterKillCount[monsterName]++;
    } else {
        entry.message = monsterName + "에게 패배...";
    }
    
    logs.push_back(entry);
}

void GameLogger::logItemUse(const string& itemName) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "ITEM";
    entry.message = itemName + " 사용";
    logs.push_back(entry);
}

void GameLogger::logGoldEarned(int amount) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "GOLD";
    entry.message = to_string(amount) + "G 획득";
    totalGoldEarned += amount;
    logs.push_back(entry);
}

void GameLogger::logGoldSpent(int amount) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "SHOP";
    entry.message = to_string(amount) + "G 사용";
    totalGoldSpent += amount;
    logs.push_back(entry);
}

void GameLogger::logExpEarned(int amount) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "EXP";
    entry.message = "경험치 +" + to_string(amount);
    totalExpEarned += amount;
    logs.push_back(entry);
}

void GameLogger::logLevelUp(int newLevel) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "LEVELUP";
    entry.message = "레벨업! 현재 레벨: " + to_string(newLevel);
    logs.push_back(entry);
}

void GameLogger::logItemFound(const string& itemName) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "ITEM";
    entry.message = itemName + " 획득!";
    totalItemsFound++;
    logs.push_back(entry);
}

void GameLogger::logItemBought(const string& itemName, int price) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "SHOP";
    entry.message = itemName + " 구매 (-" + to_string(price) + "G)";
    totalItemsBought++;
    logs.push_back(entry);
}

void GameLogger::logItemSold(const string& itemName, int price) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "SHOP";
    entry.message = itemName + " 판매 (+" + to_string(price) + "G)";
    totalItemsSold++;
    logs.push_back(entry);
}

void GameLogger::logJobSelected(const string& jobName) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = "CHARACTER";
    entry.message = "직업 선택: " + jobName;
    logs.push_back(entry);
}

void GameLogger::logCustom(const string& eventType, const string& message) {
    LogEntry entry;
    entry.timestamp = getCurrentTime();
    entry.eventType = eventType;
    entry.message = message;
    logs.push_back(entry);
}

void GameLogger::displayLogs() {
    // 한글 출력 설정
    SetConsoleOutputCP(CP_UTF8);
    
    cout << "\n========== 게임 로그 ==========\n";
    cout << "세션 시작: " << sessionStartTime << "\n\n";
    
    for (const auto& log : logs) {
        cout << "[" << log.timestamp << "] ";
        
        // 이벤트 타입별 마크
        if (log.eventType == "BATTLE") cout << "⚔ ";
        else if (log.eventType == "ITEM") cout << "📦 ";
        else if (log.eventType == "GOLD") cout << "💰 ";
        else if (log.eventType == "EXP") cout << "✨ ";
        else if (log.eventType == "LEVELUP") cout << "🎉 ";
        else if (log.eventType == "SHOP") cout << "🛒 ";
        else if (log.eventType == "CHARACTER") cout << "👤 ";
        
        cout << log.message << endl;
    }
    cout << "================================\n";
}

void GameLogger::displaySummary() {
    cout << "\n========== 플레이 요약 ==========\n";
    cout << "🎮 세션 시작 시간: " << sessionStartTime << "\n";
    cout << "⚔ 총 처치한 몬스터: " << getTotalKills() << "마리\n";
    cout << "💰 총 획득 골드: " << totalGoldEarned << "G\n";
    cout << "💸 총 사용 골드: " << totalGoldSpent << "G\n";
    cout << "💵 순 수익: " << (totalGoldEarned - totalGoldSpent) << "G\n";
    cout << "✨ 총 획득 경험치: " << totalExpEarned << "\n";
    cout << "📦 총 발견한 아이템: " << totalItemsFound << "개\n";
    cout << "🛒 구매한 아이템: " << totalItemsBought << "개\n";
    cout << "💰 판매한 아이템: " << totalItemsSold << "개\n";
    cout << "==================================\n";
}

void GameLogger::displayMonsterKills() {
    cout << "\n===== 몬스터 처치 기록 =====\n";
    if (monsterKillCount.empty()) {
        cout << "아직 처치한 몬스터가 없습니다.\n";
    } else {
        for (const auto& pair : monsterKillCount) {
            cout << "• " << pair.first << ": " << pair.second << "마리\n";
        }
        cout << "-------------------\n";
        cout << "총합: " << getTotalKills() << "마리\n";
    }
    cout << "============================\n";
}

void GameLogger::displayShopHistory() {
    cout << "\n===== 상점 거래 내역 =====\n";
    cout << "구매: " << totalItemsBought << "개 (총 " << totalGoldSpent << "G)\n";
    cout << "판매: " << totalItemsSold << "개\n";
    cout << "==========================\n";
}

int GameLogger::getTotalKills() {
    int total = 0;
    for (const auto& pair : monsterKillCount) {
        total += pair.second;
    }
    return total;
}

int GameLogger::getMonsterKillCount(const string& monsterName) {
    return monsterKillCount[monsterName];
}

void GameLogger::saveLogsToFile() {
    ofstream file("game_log.txt", ios::app);  // append 모드
    if (file.is_open()) {
        file << "\n===== 게임 세션: " << sessionStartTime << " =====\n";
        for (const auto& log : logs) {
            file << "[" << log.timestamp << "] " << log.message << "\n";
        }
        file << "\n=== 요약 ===\n";
        file << "총 처치: " << getTotalKills() << "마리\n";
        file << "획득 골드: " << totalGoldEarned << "G\n";
        file << "사용 골드: " << totalGoldSpent << "G\n";
        file << "경험치: " << totalExpEarned << "\n";
        file << "=====================================\n";
        file.close();
        cout << "로그가 game_log.txt 파일에 저장되었습니다.\n";
    }
}

void GameLogger::clearLogs() {
    logs.clear();
    monsterKillCount.clear();
    totalGoldEarned = 0;
    totalGoldSpent = 0;
    totalExpEarned = 0;
    totalItemsFound = 0;
    totalItemsBought = 0;
    totalItemsSold = 0;
}