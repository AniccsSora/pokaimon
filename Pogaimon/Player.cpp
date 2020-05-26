#include "Player.h"

Player::Player(std::string name, int x, int y)
{
	playerName = name;
	position.x = x;
	position.y = y;
}

MySpace::COORD Player::getPlayerPosition()
{
	return position;
}
