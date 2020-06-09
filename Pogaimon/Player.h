#pragma once
#include <string>
#include "Mydefine.h"
#include "Monster.h"
#include "MonsterProperty.h"

struct OverThreeMonsterUNHANDLE: public std::exception {
	std::string s;
	OverThreeMonsterUNHANDLE(std::string ss) : s(ss) {}
	~OverThreeMonsterUNHANDLE() throw() {}
	const char* what() const throw() { return s.c_str(); }
};

class Player
{
public:

	friend class Jym;// Jym 需要直接取得 monsterList

	// 玩家建構子，提供名字 以及其生成點座標。
	Player(std::string name,int x,int y);
	// Copy constructor
	Player(const Player& p);

	// 給 NPC用 的建構子，會幫他的 monsterList 初始化 number_of_monster 隻怪物。
	Player(int number_of_monster, std::string npc_name);

	// 回傳玩家現在在的座標，跟GameMap沒有半毛關係，這只是一組 "座標"。
	struct MySpace::Coordi getPlayerPosition();

	// 回傳代表此玩家的符號, Default = '@'
	char getNotation();

	// 設定玩家座標，沒有防呆他就是設定此物件的"座標"參數。
	void setPosition(MySpace::Coordi newPosition);

	// 回傳玩家 name.
	std::string getName();

	// 在 console show 出 玩家
	void showMe_by_coord();

	// 設定玩家顏色
	void setColor(rlutil_Color c);

	// 取得玩家顏色
	rlutil_Color getColor();

	// 取得玩家 持有寵物的View。
	MySpace::ViewPtr getHoldMonsterView();

	// 設定 monsterView 的位置。
	void setMonsterView_FT(int x, int y);

	// 抓到 Monster 了，會更新 monsterList、monsterView。
	void addMonster(MonsterPtr monsterCaught) throw(OverThreeMonsterUNHANDLE);

	// 抓到幾隻怪獸了
	int getMonsterListSize();

	// 取得玩家分數
	int getPoint();

	// 取得 monsterList 指定 idx 之 name(string)
	std::string getMonName_by_MonsList(int idx_of_monsterList);

	// 取得 monsterList 指定 idx 之 怪獸圖鑑的 編號。
	int getMonIDX_by_MonsList(int idx_of_monsterList);
	
	// 回傳玩家的 monsterList 的 "副本"。
	MySpace::Vec_1D_<MonsterPtr> getMonsterList();

private:
	// 玩家在地圖的位置, 1-base。
	struct MySpace::Coordi position;

	// 玩家名稱
	std::string playerName;

	// 玩家符號
	char notation = '@';

	// 玩家顏色
	int color = rlutil::WHITE;

	// 裡面存放著 monster 指標。
	MySpace::Vec_1D_<MonsterPtr> monsterList;

	// 持有怪物 ViewPtr, 從 monsterList 取得資料來顯示。// 不要是 null 就好
	MySpace::ViewPtr monsterView = NULL;

	// 玩家的對戰點數，打贏NPC 才會獲得。
	int point = 0;
};
typedef Player* PlayerPtr;

