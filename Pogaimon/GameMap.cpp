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
	int row_cnt = 0;// 計數現在處理到第幾行了
	if (mapfile.is_open())
	{
		std::vector<std::string> vec_row_tmp;
		while (getline(mapfile, line))
		{
			vec_row_tmp.clear();
			row_cnt += 1;
			// 處理 一行資料。
			for (size_t i = 0; i < line.length(); ++i) {
				vec_row_tmp.push_back(std::string(1, line[i]));// push 1 string in vector, size() only 1.
				
				// 尋找 此行 地圖資料 有無包含 NPC_CUBE。
				if (this->NPC_CUBE == line[i]) {
					MySpace::Coordi cod;
					// 1-base    
					cod.x = i + 1; cod.y = row_cnt; // row_cnt 一開始就是 1-base
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

	// 定義可站立地形字元 
	/*
	■ * 牆壁,無法穿越
	■ ; 草地, green,可以穿越
	■ ! 樹木, brown,無法穿越
	■ ~ 水池, blue,可以穿越
	■ 1-9, A, B, C,D 建築物, 無法穿越
	■ # 建築入口, yellow,可以穿越
	*/
	canStandCubes.push_back(';');
	canStandCubes.push_back('~');
	canStandCubes.push_back('#');
	canStandCubes.push_back(' ');// 別忘了 ' ' 也可以站立。
	
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

	// 紀錄 移動目的地的方塊。
	if (canStand(tar_x, tar_y)) {

		// 玩家原始位置 (Coordi 物件)
		MySpace::Coordi p_pos = player->getPlayerPosition();
		
		// 其位置的方塊。
		char last_Std_Cube = returnCubeBy(p_pos);
		
		myutil::printCube(p_pos.x, p_pos.y, last_Std_Cube);// 復原玩家站立 原本的方塊。
		myutil::printCube(tar_x, tar_y, player->getNotation());//  在新的位置 顯示玩家符號

		// update player position, 更新 player 物件。
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
	
	// 檢測欲站立的點(terrain.at(x).at(y)) 在 canStandCubes 內 就OK。
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
		cout << "Caught exception when　call terrain.at(" << y-1 << ").at("<< x-1 <<")\n";
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
		cout << "Caught exception when　call terrain.at(" << y - 1 << ").at(" << x - 1 << ")\n";
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
		// 走訪 npc_stand_corrdi_list
		for (size_t i = 0; i < this->npc_stand_corrdi_list.size(); ++i) {
			// 比對摟
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

