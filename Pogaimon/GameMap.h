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

	// copy constractor
	GameMap(const GameMap& gm);

	// �L�X �a�Ϫ����ˤl�A�|���C��C
	void showmap();

	// �L�X �a�Ϫ����ˤl�A�|���C��C���K�� ���a�]�L�W�h
	void showMap_and_Player(Player player);

	// ��� ���a��m�� show �b console �W�A�|���I���P�_�A
	// �p�G�P terrain �����a�Ϊ��A���ŦX�h���ಾ�ʹL�h�C
	void movePlayer(Player *player, int tar_x, int tar_y);

	// �^�� ���I�O�_�i�H���ߡC
	bool canStand(int x, int y);

	// �^�� terrain(�a�Ϊ���) �y��(x, y)�W ���r���C
	char returnCubeBy(int x, int y);
	char returnCubeBy(MySpace::Coordi coordi);

	// �ˬd 484 npc ������m�C(1-base)
	bool isNPCstanding(int x,int y);

	// �^�� NPC �s��(0-base.) �p�G�O �t�ƥN��o��S����NPC�C
	int return_NPC_idx(int x, int y);

private:
	// �����a�ΡA���N�O�a�ϡC
	MySpace::Vec_2D_<std::string> terrain;

	// �w�q�i���ߦa�Φr���A�p�Y�r�����w�q�b���h���{�����i���ߡC
	MySpace::Vec_1D_<char> canStandCubes;

	// �N�� NPC �� CUBE.
	char NPC_CUBE = '#';

	// �|�O���o�a�ϤW NPC ���Ҧb�y��(1-base)
	MySpace::Vec_1D_<MySpace::Coordi> npc_stand_corrdi_list;
};




