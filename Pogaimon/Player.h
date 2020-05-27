#pragma once
#include <string>
#include "Mydefine.h"

class Player
{
public:
	Player(std::string name,int x,int y);
	struct MySpace::Coordi getPlayerPosition();
	char getNotation();
	void setPosition(MySpace::Coordi newPosition);
private:
	// 玩家在地圖的位置
	struct MySpace::Coordi position;
	// 玩家名稱
	std::string playerName;
	// 玩家符號
	char notation = '@';
};

