#pragma once
#include <string>
#include "GameMap.h"
#include "Player.h"
#include <iostream>

// �����O�t�d����.
// ���Ѥ@�� �T���C�g���b�o�����O�C
class InfoProvider
{
public:
	InfoProvider(Player *player, GameMapPtr map); // do nothing
	std::string getPlayerPositionMsg();

private:
	Player* player;
	GameMapPtr map;
};

