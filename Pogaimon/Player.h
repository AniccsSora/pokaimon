#pragma once
#include <string>

namespace MySpace {
	// 保持簡單結構
	struct COORD {
		short x;
		short y;
	};
}

class Player
{
public:
	Player(std::string name,int x,int y);
	struct MySpace::COORD getPlayerPosition();
	char getNotation();
	void setPosition(MySpace::COORD newPosition);
private:
	// 玩家在地圖的位置
	struct MySpace::COORD position;
	// 玩家名稱
	std::string playerName;
	// 玩家符號
	char notation = '@';
};

