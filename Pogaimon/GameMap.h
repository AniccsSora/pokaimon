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
	// �q�ɮרt�� Ū�� map�ɡA�H�Τ@�Ǫ�l�ơC
	GameMap(std::string filename);

	// �L�X �a�Ϫ����ˤl�A�|���C��C
	void showmap();

	// ��� ���a��m�� show �b console �W�A�|���I���P�_�A
	// �p�G�P terrain �����a�Ϊ��A���ŦX�h���ಾ�ʹL�h�C
	void movePlayer(Player *player, int tar_x, int tar_y);

	// �^�� ���I�O�_�i�H���ߡC
	bool canStand(int x, int y);

	// �^�� terrain(�a�Ϊ���) �y��(x, y)�W ���r���C
	char returnCubeBy(int x, int y);
	char returnCubeBy(MySpace::Coordi coordi);

private:
	// �����a�ΡA���N�O�a�ϡC
	MySpace::Vec_2D_<std::string> terrain;

	// �w�q�i���ߦa�Φr���A�p�Y�r�����w�q�b���h���{�����i���ߡC
	MySpace::Vec_1D_<char> canStandCubes;
};




