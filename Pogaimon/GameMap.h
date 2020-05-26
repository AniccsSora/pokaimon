#pragma once
#include <iostream>
#include <fstream>
#include <vector>
class GameMap
{
public:
	GameMap(std::string filename);
	// 印出 地圖長的樣子。 除錯用func。
	void showmap();
private:
	// 紀錄地形
	std::vector<std::vector<std::string>> terrain;
};

