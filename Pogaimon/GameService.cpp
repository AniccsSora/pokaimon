#include "GameService.h"
#include "Myutil.h"
#include "MonsterProperty.h"
#include "Player.h"
GameService::GameService(GameMapPtr map)
{
	// ��l�� 
	this->map = new GameMap(*map);

	this->mstPropertyList = myutil::loadMonsterFile();

	// ��l�� NPC_list
	for (int i = 0; i < map->get_number_of_NPC(); i++) {
		this->NPC_list.push_back(new Player(3)); // �C�� NPC ���T����
	}
	// ===========================

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
	else if ( '#' == playerStandCube) { // �J�� NPC
		// ���o NPC player ����A���n�����o NPC �s��
		int npc_id = this->map->return_NPC_idx(player->getPlayerPosition().x, player->getPlayerPosition().y);
		// �q GameService �����o�ӽs�� NPC ����C
		PlayerPtr encounterNPC = this->NPC_list.at(npc_id);
		
		rtnEvent = new EncounterNPCEvent(player, encounterNPC);
	}
	else {
		rtnEvent = new NoneEvent();
	}


	return rtnEvent;
}

PlayerPtr GameService::getNPC(int idx)
{
	return this->NPC_list.at(idx);
}
