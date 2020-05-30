#pragma once
#include <string>
#include "GameMap.h"
#include "Player.h"
#include <iostream>

// 此類別負責提取.
// 提供一些 訊息。寫死在這個類別。
class InfoProvider
{
public:
	InfoProvider(Player *player, GameMapPtr map); // do nothing
	std::string getPlayerPositionMsg();

private:
	Player* player;
	GameMapPtr map;
};

