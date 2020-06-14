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
		PlayerPtr npc = new Player(3, std::string("NPC_" + std::to_string(i)));
		npc->setPosition(this->map->getNPC_Corri_by_idx(i));
		this->NPC_list.push_back(npc); // 每個 NPC 有三隻怪
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
	if ( ';' == playerStandCube || '~' == playerStandCube || ' ' == playerStandCube){
		if (myutil::X_Probability_get_True(ENCOUBTER_MONSTER_P)) { //myutil::X_Probability_get_True(ENCOUBTER_MONSTER_P)

		    // 生成 Event , 要包 monster 物件所以要傳 寵物數值 參考表。
		
			// 0 1 2 草 0-Base, 強制生草怪物 給此玩家 10% 上升 40% ~= 0.14.
			if (';' == playerStandCube && myutil::X_Probability_get_True(0.14)) {
				rtnEvent = new EncounterMonsterEvent(this->mstPropertyList, player, 1);
			}
			// 6 7 8 水 0-Base, 強制生水怪物 給此玩家 10% 上升 40% ~= 0.14.
			else if ('~' == playerStandCube && myutil::X_Probability_get_True(0.14)) {
				rtnEvent = new EncounterMonsterEvent(this->mstPropertyList, player, 2);
			}
			else { // 預設機率
				rtnEvent = new EncounterMonsterEvent(this->mstPropertyList, player, 0);
			}

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
