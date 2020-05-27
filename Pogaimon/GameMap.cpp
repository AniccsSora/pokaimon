#include "GameMap.h"
#include "Player.h"
#include "rlutil.h"
#include "Myutil.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

GameMap::GameMap(std::string filename)
{
	std::string line;
	std::ifstream mapfile(filename);
	// ���O�� �w�]���C��A���� handle �ܼƨS���Y�C
	
	if (mapfile.is_open())
	{
		std::vector<std::string> vec_row_tmp;
		while (getline(mapfile, line))
		{
			vec_row_tmp.clear();
			// �B�z �@���ơC
			for (auto i = 0; i < line.length(); i++) {
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
	for (auto i = 0; i < terrain.size(); i++) {
		for (auto j = 0; j < terrain.at(i).size(); j++) {
			std::cout << terrain.at(i).at(j);
		}std::cout << "\n";
	}std::cout << "\n";
}

void GameMap::movePlayer(Player &player, int tar_x, int tar_y)
{

	// ���� ���ʥت��a������C
	if (canStand(tar_x, tar_y)) {
		// ���a��l��m
		MySpace::Coordi p_pos = player.getPlayerPosition();
		rlutil::locate(p_pos.x, p_pos.y); // �쥻���a��m
		std::cout << " ";// erease player notation.
		rlutil::locate(tar_x, tar_y); // ���a�����ʦ�m
		std::cout << player.getNotation();// show player notation.
		// update player position
		MySpace::Coordi newPos; newPos.x = tar_x; newPos.y = tar_y;
		rlutil::locate(1, 37);
		cout << "���a��m���Ӧb����m : x: " << newPos.x
			<< ", y: " << newPos.y << endl;
		player.setPosition(newPos);
		myutil::update_log("�w�g���� �B�i����");
		return;
	}
	myutil::update_log("���i����");
	
}

bool GameMap::canStand(int x, int y)
{
	bool rtn = false;
	
	// �˴������ߪ��I(terrain.at(x).at(y)) �b canStandCubes �� �NOK�C
	for (auto i = 0; i < canStandCubes.size(); i++) {
		char wantStandCube = returnCubeBy(x,y);
		rlutil::locate(1, 33);
		cout << "\rlog: " << "wantStandCube: \"" << wantStandCube  << "\"" << endl;
		rlutil::locate(1, 34);
		cout << "\rlog: " << "returnCubeBy(" <<  x << "," << y << ")="
			<< "\"" << returnCubeBy(x,y) << "\""<< endl;
		if (canStandCubes[i] == wantStandCube) {
			rtn = true;
			break;
		}
	}
	
	return rtn;
}

char GameMap::returnCubeBy(int x, int y)
{
	return (char)terrain.at(y-1).at(x-1)[0]; // have exception risk.
}
