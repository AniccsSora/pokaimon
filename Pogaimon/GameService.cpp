#include "GameService.h"
#include "Myutil.h"
#include "MonsterProperty.h"
#include "Player.h"
GameService::GameService(GameMapPtr map)
{
	this->map = new GameMap(*map);
	this->mstPropertyList = myutil::loadMonsterFile();
}

Event* GameService::getEvent(Player* player)
{
	// �`�N �o��|�̷Ӥ��P�� player���A �^�Ǥ��P�� Event ����~
	Event* rtnEvent = NULL;

	// ���a�ثe���ߪ� ���
	char playerStandCube = this->map->returnCubeBy(player->getPlayerPosition());

	// �J�����O ';'�A�O�����vĲ�o��~~ 
	if ( ';' == playerStandCube ){
		if ( 1 ) { //myutil::X_Probability_get_True(ENCOUBTER_MONSTER_P)

			// �� Event , �n�] monster ����ҥH�n�� �d���ƭ� �ѦҪ�C
			rtnEvent = new EncounterMonsterEvent(this->mstPropertyList, player);
		}
		else {
			rtnEvent = new NoneEvent();
		}
		
	}
	else if (false) {

	}
	else {
		rtnEvent = new NoneEvent();
	}


	return rtnEvent;
}
