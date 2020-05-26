#include "GameMap.h"
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
}

void GameMap::showmap()
{
	for (auto i = 0; i < terrain.size(); i++) {
		for (auto j = 0; j < terrain.at(i).size(); j++) {
			std::cout << terrain.at(i).at(j);
		}std::cout << "\n";
	}std::cout << "\n";
}
