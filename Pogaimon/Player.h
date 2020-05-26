#pragma once
#include <string>

namespace MySpace {
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
private:
	// 玩家在地圖的位置
	struct MySpace::COORD position;
	// 玩家名稱
	std::string playerName;
};

