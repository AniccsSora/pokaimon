#pragma once
#include "GameMap.h"
#include "Player.h"
#include "Event.h"
#include "MonsterProperty.h"


// �J�� �Ǫ������v
#define ENCOUBTER_MONSTER_P 0.1

class GameService
{
public:

	// �ƻs�@�� map ��������C
	GameService(GameMapPtr map);

	// �^�� ���a�{�b�� Event�A�oEvent�|�D�`���Ȼs�ơA�^�� Event �l���O�C�L�| new
	Event* getEvent(Player* player);
	/* �ɥR: C++ �����o�^�� �µ������O�� "����"�A �ڭ̥u��H���Ф覡���� abstract class.*/


private:
	GameMapPtr map = NULL;
	MonsterPropertyList mstPropertyList;
};

