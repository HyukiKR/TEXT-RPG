#pragma once
#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <map>

using namespace std;

struct LogEntry {
    string timestamp;
    string eventType;  // "BATTLE", "ITEM", "GOLD", "LEVELUP", "SHOP", etc.
    string message;
};

class GameLogger {
private:
    static GameLogger* instance;
    vector<LogEntry> logs;
    map<string, int> monsterKillCount;  // 몬스터별 처치 횟수
    int totalGoldEarned;
    int totalGoldSpent;
    int totalExpEarned;
    int totalItemsFound;
    int totalItemsBought;
    int totalItemsSold;
    string sessionStartTime;
    
    GameLogger();
    string getCurrentTime();
    
public:
    static GameLogger* getInstance();
    
    // 로그 기록 메서드
    void logBattle(const string& monsterName, bool victory);
    void logItemUse(const string& itemName);
    void logGoldEarned(int amount);
    void logGoldSpent(int amount);
    void logExpEarned(int amount);
    void logLevelUp(int newLevel);
    void logItemFound(const string& itemName);
    void logItemBought(const string& itemName, int price);
    void logItemSold(const string& itemName, int price);
    void logJobSelected(const string& jobName);
    void logCustom(const string& eventType, const string& message);
    
    // 로그 표시 메서드
    void displayLogs();
    void displaySummary();
    void displayMonsterKills();
    void displayShopHistory();
    void saveLogsToFile();
    void clearLogs();
    
    // Getter
    int getTotalKills();
    int getMonsterKillCount(const string& monsterName);
};

#endif