#include "GameMap.h"
#include "Player.h"
#include "rlutil.h"
#include "Myutil.h"
#include "Mydefine.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

GameMap::GameMap(std::string filename)
{
	std::string line;
	std::ifstream mapfile(filename);
	int row_cnt = 0;// �p�Ʋ{�b�B�z��ĴX��F
	if (mapfile.is_open())
	{
		std::vector<std::string> vec_row_tmp;
		while (getline(mapfile, line))
		{
			vec_row_tmp.clear();
			row_cnt += 1;
			// �B�z �@���ơC
			for (size_t i = 0; i < line.length(); ++i) {
				vec_row_tmp.push_back(std::string(1, line[i]));// push 1 string in vector, size() only 1.
				
				// �M�� ���� �a�ϸ�� ���L�]�t NPC_CUBE�C
				if (this->NPC_CUBE == line[i]) {
					MySpace::Coordi cod;
					// 1-base    
					cod.x = i + 1; cod.y = row_cnt; // row_cnt �@�}�l�N�O 1-base
					this->npc_stand_corrdi_list.push_back(cod);
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

GameMap::GameMap(const GameMap& gm)
{
	MySpace::Vec_1D_<char> copiedTerrain(gm.canStandCubes);
	MySpace::Vec_2D_<std::string> copiedMap(gm.terrain);
	this->terrain = copiedMap;
	this->canStandCubes = copiedTerrain;
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
		player->setPosition(newPos);
		
		return;
	}
	else {
		return ;// pass
	}
	
	
}

bool GameMap::canStand(int x, int y)
{
	bool rtn = false;
	
	// �˴������ߪ��I(terrain.at(x).at(y)) �b canStandCubes �� �NOK�C
	for (size_t i = 0; i < canStandCubes.size(); i++) {
		char wantStandCube = returnCubeBy(x,y);
		
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

bool GameMap::isNPCstanding(int x, int y){
	bool flag = false;

	if (this->returnCubeBy(x, y) == this->NPC_CUBE) {
		flag = true;
	}

	return flag;
}

int GameMap::return_NPC_idx(int x, int y){
	int rtnIdx = -1;

	if (isNPCstanding(x,y)){
		// ���X npc_stand_corrdi_list
		for (size_t i = 0; i < this->npc_stand_corrdi_list.size(); ++i) {
			// ���O
			if ( npc_stand_corrdi_list[i].x == x && 
				 npc_stand_corrdi_list[i].y == y) {
				rtnIdx = i;
				break;
			}
		}
	}
	else {
		rtnIdx = -1;
	}

	return rtnIdx;
}

