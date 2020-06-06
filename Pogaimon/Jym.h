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

	// 一個玩家會有對應於 monsterList 數量的 Displayer,
	// 每個 Displayer 都有 ASCII, 寵物屬性。
	MySpace::Vec_1D_<Displayer> P1_DisplayerList;
	MySpace::Vec_1D_<Displayer> P2_DisplayerList;

	// 持有寵物清單
	Displayer P1_holdMonster_Displayer;
	Displayer P2_holdMonster_Displayer;
	
	// 戰鬥訊息總是會更新，所以不必不同怪獸不同 Displayer。											
	Displayer battle_log;
};


