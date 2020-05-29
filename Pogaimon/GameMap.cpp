#include "GameMap.h"
#include "Player.h"
#include "rlutil.h"
#include "Myutil.h"
#include "Mydefine.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

GameMap::GameMap(std::string filename)
{
	std::string line;
	std::ifstream mapfile(filename);
	
	if (mapfile.is_open())
	{
		std::vector<std::string> vec_row_tmp;
		while (getline(mapfile, line))
		{
			vec_row_tmp.clear();
			// �B�z �@���ơC
			for (size_t i = 0; i < line.length(); i++) {
				{
					vec_row_tmp.push_back(std::string(1, line[i]));
				}
			}
			terrain.push_back(vec_row_tmp);
			// GOTO next line
		}
		mapfile.close();
	}
	else {
		std::cout << "Unable to open file: " << "\"" << filename << "\"" << std::endl;
	}

	// �w�q�i���ߦa�Φr�� 
	/*
	�� * ���,�L�k��V
	�� ; ��a, green,�i�H��V
	�� ! ���, brown,�L�k��V
	�� ~ ����, blue,�i�H��V
	�� 1-9, A, B, C,D �ؿv��, �L�k��V
	�� # �ؿv�J�f, yellow,�i�H��V
	*/
	canStandCubes.push_back(';');
	canStandCubes.push_back('~');
	canStandCubes.push_back('#');
	canStandCubes.push_back(' ');// �O�ѤF ' ' �]�i�H���ߡC
	
}

void GameMap::showmap()
{
	rlutil::locate(1, 1);
	for (size_t i = 0; i < terrain.size(); i++) {
		for (size_t j = 0; j < terrain.at(i).size(); j++) {
			myutil::printCube(-1,-1, (char)terrain.at(i).at(j)[0]);
		}std::cout << "\n";
	}std::cout << "\n";
}

void GameMap::showMap_and_Player(Player player)
{
	showmap();
	player.showMe_by_coord();
}



void GameMap::movePlayer(Player *player, int tar_x, int tar_y)
{

	// ���� ���ʥت��a������C
	if (canStand(tar_x, tar_y)) {

		// ���a��l��m (Coordi ����)
		MySpace::Coordi p_pos = player->getPlayerPosition();
		
		// ���m������C
		char last_Std_Cube = returnCubeBy(p_pos);
		
		myutil::printCube(p_pos.x, p_pos.y, last_Std_Cube);// �_�쪱�a���� �쥻������C
		myutil::printCube(tar_x, tar_y, player->getNotation());//  �b�s����m ��ܪ��a�Ÿ�

		// update player position, ��s player ����C
		MySpace::Coordi newPos; newPos.x = tar_x; newPos.y = tar_y;
		rlutil::locate(1, 37);
		cout << "���a��m���Ӧb����m : x: " << newPos.x
			<< ", y: " << newPos.y << endl;
		player->setPosition(newPos);
		myutil::update_log("�w�g���� �B�i����");
		return;
	}
	else {
		std::string msg = std::string("�����a " + player->getName() + " ���i���ʦ� (" + std::to_string(tar_x) + ", " + std::to_string(tar_y) + ")");
		myutil::update_log(msg);
	}
	
	
}

bool GameMap::canStand(int x, int y)
{
	bool rtn = false;
	
	// �˴������ߪ��I(terrain.at(x).at(y)) �b canStandCubes �� �NOK�C
	for (size_t i = 0; i < canStandCubes.size(); i++) {
		char wantStandCube = returnCubeBy(x,y);
		rlutil::locate(1, 34);
		cout << "\rlog: " << "returnCubeBy(" <<  x << "," << y << ")="
			<< "\'" << returnCubeBy(x,y) << "\'"<< endl;
		if (canStandCubes[i] == wantStandCube) {
			rtn = true;
			break;
		}
	}
	
	return rtn;
}

char GameMap::returnCubeBy(int x, int y) throw(...)
{
	try {
		return (char)terrain.at(y - 1).at(x - 1)[0]; // have exception risk.
	}
	catch (...) {
		cout << "Caught exception when�@call terrain.at(" << y-1 << ").at("<< x-1 <<")\n";
		cout << "... target index size()= " << terrain.at(y - 1).at(x - 1).size() << ".\n";
		exit(0);
	}
}

char GameMap::returnCubeBy(MySpace::Coordi coordi)
{
	int x = coordi.x; int y = coordi.y;
	
	try {
		return (char)terrain.at(y - 1).at(x - 1)[0]; // have exception risk.
	}
	catch (...) {
		cout << "Caught exception when�@call terrain.at(" << y - 1 << ").at(" << x - 1 << ")\n";
		cout << "... target index size()= " << terrain.at(y - 1).at(x - 1).size() << ".\n";
		exit(0);
	}
}

