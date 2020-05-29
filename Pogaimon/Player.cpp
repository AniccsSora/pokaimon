#include "Player.h"
#include "Mydefine.h"
#include "GameMap.h"

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

std::string Player::getName()
{
	return playerName;
}

char Player::getStandCube()
{
	return ' ';
}

void Player::showMe_by_coord()
{
	rlutil::locate(position.x, position.y);
	std::cout << notation;
}


