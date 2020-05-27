#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"

typedef std::vector<std::vector<std::string>> Vec_2D;
typedef std::vector<char> Vec_CH;

class GameMap
{
public:
	// 從檔案系統 讀取 map檔，以及一些初始化。
	GameMap(std::string filename);
	// 印出 地圖長的樣子。 除錯用func。
	void showmap();
	// 顯示 玩家位置，並顯示在 MAP上，會做碰撞判斷，
	// 如果與 terrain 內的地形狀態不符合則不能移動過去。
	void movePlayer(Player &player, int tar_x, int tar_y);
	// 回傳 該點是否可以站立。
	bool canStand(int x, int y);
	// 
	char returnCubeBy(int x, int y);
private:
	// 紀錄地形
	Vec_2D terrain;
	// 定義可站立地形字元，如某字元未定義在內則都認為不可站立。
	Vec_CH canStandCubes;

};

