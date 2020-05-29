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
			// 處理 一行資料。
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
		rlutil::locate(1, 37);
		cout << "玩家位置應該在的位置 : x: " << newPos.x
			<< ", y: " << newPos.y << endl;
		player->setPosition(newPos);
		myutil::update_log("已經移動 且可移動");
		return;
	}
	else {
		std::string msg = std::string("此玩家 " + player->getName() + " 不可移動至 (" + std::to_string(tar_x) + ", " + std::to_string(tar_y) + ")");
		myutil::update_log(msg);
	}
	
	
}

bool GameMap::canStand(int x, int y)
{
	bool rtn = false;
	
	// 檢測欲站立的點(terrain.at(x).at(y)) 在 canStandCubes 內 就OK。
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

