#pragma once
#include "GameMap.h"
#include "Player.h"
#include "Event.h"
#include "MonsterProperty.h"

// 遇到 怪物的機率
#define ENCOUBTER_MONSTER_P 0.1

class GameService
{
public:

	// 複製一份 map 給此物件。
	GameService(GameMapPtr map);

	// 回報 玩家現在的 Event，這Event會非常的客製化，回給 Event 子類別。他會 new
	Event* getEvent(Player* player);
	/* 補充: C++ 內不得回傳 純虛擬類別的 "實體"， 我們只能以指標方式指到 abstract class.*/

	// 回傳指定 NPC編號 PlayerPtr物件
	PlayerPtr getNPC(int idx);

private:
	// 地圖物件
	GameMapPtr map = NULL;
	// 寵物圖鑑，所有的寵物資訊會存在這個表
	MonsterPropertyList mstPropertyList;
	// 儲存 NPC player 物件
	MySpace::Vec_1D_<PlayerPtr> NPC_list;
};

