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
	// ���a�b�a�Ϫ���m
	struct MySpace::Coordi position;
	// ���a�W��
	std::string playerName;
	// ���a�Ÿ�
	char notation = '@';
};

