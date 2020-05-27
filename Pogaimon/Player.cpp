#include "Player.h"
#include "Mydefine.h"

Player::Player(std::string name, int x, int y)
{
	playerName = name;
	position.x = x;
	position.y = y;
}

MySpace::Coordi Player::getPlayerPosition()
{
	return position;
}

char Player::getNotation()
{
	return notation;
}

void Player::setPosition(MySpace::Coordi newPosition)
{
	position = newPosition;
}
