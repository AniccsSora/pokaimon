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
	else if (false) {

	}
	else {
		rtnEvent = new NoneEvent();
	}


	return rtnEvent;
}
