#pragma once
#include "Player.h"
#include "Displayer.h"
#include "Mydefine.h"
#include "Myutil.h"

// 兩位玩家要對戰就來這邊，把 (Player)X 2  傳進來，裡面會需要很多的東東
class Jym{
public:
	// 建構子
	Jym(Player& P1, Player& P2);
	// 直接開打
	void battle_start();

private:

	// ===================== < 對戰畫面 View 參數設定區>
	// 這些參數是依照 PDF 開的規格去評估的。

	//決定 多少高度 "開始"印出 屬性 View，因為 ASCII 高度有待評估。
	int limit_of_property = 30;
	// 決定 console 的哪邊開始要分一半。開始印出 P2 的資料
	int half_x = 70;

	// P1,P2 開始印 ascii View 的座標
	int P1_asciiView_X = 1, P1_asciiView_Y = 1;
	int P2_asciiView_X = 92, P2_asciiView_Y = 1;

	// P1, P2 寵物屬性 Property View 座標
	int P1_pp_view_X = 41, P1_pp_view_Y = 5;
	int P2_pp_view_X = 134, P2_pp_view_Y = 5;

	// P1，P2 開始印 持有寵物 View 的座標
	int P1_ViewHoldMos_X = P1_pp_view_X, P1_ViewHoldMos_Y = 26;
	int P2_ViewHoldMos_X = P2_pp_view_X, P2_ViewHoldMos_Y = 26;

	// Log 開始印的高度
	int log_x = 40, log_y = 37;
	// ===================== </對戰畫面 View 參數設定區>

	PlayerPtr P1 = NULL;
	PlayerPtr P2 = NULL;

	int P1_hold_mosterN = -1;// P1 持有的怪物總數。1-base
	int P2_hold_mosterN = -1;// P2 持有的怪物總數

	int P1_canBattle_mon_idx = -1;// P1 目前可以戰鬥的 怪物 指標。0-base
	int P2_canBattle_mon_idx = -1;// P2 目前可以戰鬥的 怪物 指標。

	// 一些在 Jym 裡面呼叫的函式。

	// 是否雙方玩家都可以戰鬥?
	bool bothPlayerCanFight();

	// 確認雙方 怪獸 是否可以戰鬥
	bool bothMonsterCanFight(MonsterPtr P1_mons, MonsterPtr P2_mons);

	// 根據現在的形情 Property 去更新 View, 兩位玩家都更新。
	void updatePropertyView();

	// 寵物攻擊 的方法，內部會直接修改 寵物的 Property。
	void fight(MonsterPtr M1, MonsterPtr M2);


	// 取得玩家目前可以戰鬥的寵物。(參考 P?_canBattle_mon_idx 的數值做決定)
	MonsterPtr pickCanBattleMonster(PlayerPtr player);

	// 印出 log, 簡化呼叫用的。
	inline void showlog();

	inline void clearLog();

	// 一個玩家會有對應於 monsterList 數量的 Displayer,
	// 每個 Displayer 都有 ASCII, 寵物屬性。
	MySpace::Vec_1D_<Displayer> P1_ASCII_DList;
	MySpace::Vec_1D_<Displayer> P2_ASCII_DList;

	// 寵物屬性 Displayer List
	MySpace::Vec_1D_<Displayer> P1_MProperty_DList;
	MySpace::Vec_1D_<Displayer> P2_MProperty_DList;
	
	// 持有寵物清單
	Displayer P1_holdMonster_Displayer;
	Displayer P2_holdMonster_Displayer;
	
	// 戰鬥訊息總是會更新，所以不必不同怪獸不同 Displayer。											
	Displayer battle_log;
	// 放到 battle_log 的 View, 因為放入的指標，所以直接修改battleLog_view 就可以影響到 Displayer.
	int logRowSize = 9;
	int logColSize = 120;
	MySpace::ViewPtr battleLog_view = myutil::createView('=', logRowSize, logColSize);
	
};

