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

	// 寵物(ASCII) = 圖示對應 monsterList 順序
	MySpace::Vec_1D_<MySpace::ViewPtr> P1_ascii_veiwList;
	MySpace::Vec_1D_<MySpace::ViewPtr> P2_ascii_veiwList;

	// 管理、寵物屬性、持有寵物清單 的 Displayer 物件。
	Displayer P1_ViewManager;
	Displayer P1_mons_asciiManager; // 只放一個View，也只用第一個View，要使用時才會 呼叫, 不用初始化
	Displayer P2_ViewManager;
	Displayer P2_mons_asciiManager; // 只放一個View，也只用第一個View，要使用時才會 呼叫, 不用初始化
	Displayer battle_log;
};


