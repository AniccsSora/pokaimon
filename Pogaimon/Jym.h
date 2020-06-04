#pragma once
#include "Player.h"
#include "Displayer.h"
#include "Mydefine.h"
#include "Myutil.h"

// 兩位玩家要對戰就來這邊，把 (Player)X 2  傳進來，裡面會需要很多的東東
class Jym{
public:
	// 建構子
	Jym(PlayerPtr P1, PlayerPtr P2);
	// 直接開打
	void battle_start();

private:
	PlayerPtr P1 = NULL;
	PlayerPtr P2 = NULL;

	// 管理P1 寵物(ASCII)、寵物屬性、持有寵物清單 的 Displayer 物件。
	Displayer P1_ViewManager;
	Displayer P2_ViewManager;
	Displayer battle_log;
};

