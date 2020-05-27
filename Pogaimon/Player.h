#pragma once
#include <string>

namespace MySpace {
	// �O��²�浲�c
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
	// ���a�b�a�Ϫ���m
	struct MySpace::COORD position;
	// ���a�W��
	std::string playerName;
	// ���a�Ÿ�
	char notation = '@';
};

