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
	std::string pos_msg = "���a��m : x: " + std::to_string(player->getPlayerPosition().x) +
		", y: " + std::to_string(player->getPlayerPosition().y) +
		", ����cube = \"" + map->returnCubeBy(x, y) + "\"\n";

	return pos_msg;
}
