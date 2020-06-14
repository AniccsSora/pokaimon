#pragma once
#include <string>
#include "Monster.h"
#include "MonsterProperty.h"
#include "Mydefine.h"
#include "Displayer.h"
#include "Myutil.h"
#include "rlutil.h"
#include "Jym.h"

// Event 父類別
class Event
{
public :
	// Do nothing
	Event(){};

	// 觸發此事件，由子類別實做
	virtual void touchOff() = 0; //  = 0, 宣告成 pure virtual function

protected:
	
};

// 遭遇 Monster 事件
class EncounterMonsterEvent : public Event {

public:
	// 建構子
	EncounterMonsterEvent(MonsterPropertyList mstPropertyList, Player* servicedPlayer,int createStrategyCode);

	// 實作 父類別的 pure virtual function...(必須加上 virtual 關鍵字)
	virtual void touchOff();

private:
	// 確認是否要抓怪
	//void showStartBattleDialog();
	Monster* encounterMonster =NULL; // EncounterMonsterEvent 建構子會給此數值
	Displayer* eventViewList = NULL; // 遊戲畫面~~
	Player* servicedPlayer = NULL;
	MySpace::ViewPtr log_content_view = NULL;
};

// 玩家遇到 NPC，準備對戰 Event。
class EncounterNPCEvent : public Event {
public:
	// 建構子
	EncounterNPCEvent(Player* player, PlayerPtr encounterNpc);
	// 遇到 NPC 時的實作, 這邊會有一個 道館(Gym) 物件在內部。 所用到參數會是複製過的。
	virtual void touchOff();

private:
	// 玩家本人
	PlayerPtr player = NULL;
	// 遇到的 NPC
	PlayerPtr encounterNpc;
};

// 沒有事件，如果玩家站在 非特殊方塊時會回傳此物件。
class NoneEvent : public Event {

	//建構子不用寫~ 用預設的。

	// 無實作，但不寫實作這類別會被認為是 abstract class.
	// 實作 父類別的 pure virtual function...(必須加上 virtual 關鍵字)
	virtual void touchOff() {
		; // nothing
	}
};

