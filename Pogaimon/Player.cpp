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

char Player::getNotation()
{
	return notation;
}

void Player::setPosition(MySpace::COORD newPosition)
{
	position = newPosition;
}
