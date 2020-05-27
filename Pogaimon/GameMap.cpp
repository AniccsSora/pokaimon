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
	// 先記錄 預設的顏色，不用 handle 變數沒關係。
	
	if (mapfile.is_open())
	{
		std::vector<std::string> vec_row_tmp;
		while (getline(mapfile, line))
		{
			vec_row_tmp.clear();
			// 處理 一行資料。
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
	for (auto i = 0; i < terrain.size(); i++) {
		for (auto j = 0; j < terrain.at(i).size(); j++) {
			std::cout << terrain.at(i).at(j);
		}std::cout << "\n";
	}std::cout << "\n";
}

void GameMap::movePlayer(Player &player, int tar_x, int tar_y)
{

	// 紀錄 移動目的地的方塊。
	if (canStand(tar_x, tar_y)) {
		// 玩家原始位置
		MySpace::Coordi p_pos = player.getPlayerPosition();
		rlutil::locate(p_pos.x, p_pos.y); // 原本玩家位置
		std::cout << " ";// erease player notation.
		rlutil::locate(tar_x, tar_y); // 玩家欲移動位置
		std::cout << player.getNotation();// show player notation.
		// update player position
		MySpace::Coordi newPos; newPos.x = tar_x; newPos.y = tar_y;
		rlutil::locate(1, 37);
		cout << "玩家位置應該在的位置 : x: " << newPos.x
			<< ", y: " << newPos.y << endl;
		player.setPosition(newPos);
		myutil::update_log("已經移動 且可移動");
		return;
	}
	myutil::update_log("不可移動");
	
}

bool GameMap::canStand(int x, int y)
{
	bool rtn = false;
	
	// 檢測欲站立的點(terrain.at(x).at(y)) 在 canStandCubes 內 就OK。
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
