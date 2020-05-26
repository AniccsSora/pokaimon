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
	// ���a�b�a�Ϫ���m
	struct MySpace::COORD position;
	// ���a�W��
	std::string playerName;
};

