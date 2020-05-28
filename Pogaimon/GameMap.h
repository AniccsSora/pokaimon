#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Mydefine.h"

// Prototype "GameMap" because below typedef.
class GameMap;

typedef GameMap* GameMapPtr;

class GameMap
{
public:
	// 從檔案系統 讀取 map檔，以及一些初始化。
	GameMap(std::string filename);

	// 印出 地圖長的樣子，會有顏色。
	void showmap();

	// 顯示 玩家位置並 show 在 console 上，會做碰撞判斷，
	// 如果與 terrain 內的地形狀態不符合則不能移動過去。
	void movePlayer(Player *player, int tar_x, int tar_y);

	// 回傳 該點是否可以站立。
	bool canStand(int x, int y);

	// 回傳 terrain(地形物件) 座標(x, y)上 的字元。
	char returnCubeBy(int x, int y);
	char returnCubeBy(MySpace::Coordi coordi);

private:
	// 紀錄地形，其實就是地圖。
	MySpace::Vec_2D_<std::string> terrain;

	// 定義可站立地形字元，如某字元未定義在內則都認為不可站立。
	MySpace::Vec_1D_<char> canStandCubes;
};




