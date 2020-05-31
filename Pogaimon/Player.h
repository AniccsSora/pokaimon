#pragma once
#include <string>
#include "Mydefine.h"


class Player
{
public:
	// 玩家建構子，提供名字 以及其生成點座標。
	Player(std::string name,int x,int y);

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

	//

private:
	// 玩家在地圖的位置, 1-base。
	struct MySpace::Coordi position;

	// 玩家名稱
	std::string playerName;

	// 玩家符號
	char notation = '@';

	// 玩家顏色
	int color = rlutil::WHITE;
};

