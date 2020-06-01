#include "InfoProvider.h"

InfoProvider::InfoProvider(Player* player, GameMapPtr map)
{
	this->map = map;
	this->player = player;
}

std::string InfoProvider::getPlayerPositionMsg()
{	
	short x = player->getPlayerPosition().x;
	short y = player->getPlayerPosition().y;
	std::string pos_msg = std::string(10,' ') + 
		"Player pos : x: " + std::to_string(player->getPlayerPosition().x) +
		        ", y: " + std::to_string(player->getPlayerPosition().y) +
		", stand cube = \"" + map->returnCubeBy(x, y) + "\"";

	return pos_msg;
}
