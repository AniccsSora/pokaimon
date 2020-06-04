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

	// �^�ǫ��w NPC�s�� PlayerPtr����
	PlayerPtr getNPC(int idx);

private:
	// �a�Ϫ���
	GameMapPtr map = NULL;
	// �d����Ų�A�Ҧ����d����T�|�s�b�o�Ӫ�
	MonsterPropertyList mstPropertyList;
	// �x�s NPC player ����
	MySpace::Vec_1D_<PlayerPtr> NPC_list;
};

