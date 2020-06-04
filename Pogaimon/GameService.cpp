#include "GameService.h"
#include "Myutil.h"
#include "MonsterProperty.h"
#include "Player.h"
GameService::GameService(GameMapPtr map)
{
	// 初始化 
	this->map = new GameMap(*map);

	this->mstPropertyList = myutil::loadMonsterFile();

	// 初始化 NPC_list
	for (int i = 0; i < map->get_number_of_NPC(); i++) {
		this->NPC_list.push_back(new Player(3)); // 每個 NPC 有三隻怪
	}
	// ===========================

}

Event* GameService::getEvent(Player* player)
{
	// 注意 這邊會依照不同的 player狀態 回傳不同的 Event 物件~
	Event* rtnEvent = NULL;

	// 玩家目前站立的 方塊
	char playerStandCube = this->map->returnCubeBy(player->getPlayerPosition());

	// 遇到到草叢 ';'，是有機率觸發的~~ 
	if ( ';' == playerStandCube ){
		if ( 1 ) { //myutil::X_Probability_get_True(ENCOUBTER_MONSTER_P)

			// 生 Event , 要包 monster 物件所以要傳 寵物數值 參考表。
			rtnEvent = new EncounterMonsterEvent(this->mstPropertyList, player);
		}
		else {
			rtnEvent = new NoneEvent();
		}
		
	}
	else if ( '#' == playerStandCube) { // 遇到 NPC
		// 取得 NPC player 物件，那要先取得 NPC 編號
		int npc_id = this->map->return_NPC_idx(player->getPlayerPosition().x, player->getPlayerPosition().y);
		// 從 GameService 的取得該編號 NPC 物件。
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
