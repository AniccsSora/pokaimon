#pragma once
#include <iostream>
#include <fstream>
#include <vector>
class GameMap
{
public:
	GameMap(std::string filename);
	// �L�X �a�Ϫ����ˤl�C ������func�C
	void showmap();
private:
	// �����a��
	std::vector<std::vector<std::string>> terrain;
};

