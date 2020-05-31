#include "Event.h"



// 建構子
EncounterMonsterEvent::EncounterMonsterEvent(MonsterPropertyList mstPropertyList,Player* servicedPlayer):Event(){
	// 隨便生一個怪物~~
	this->monster = new Monster(rand(), mstPropertyList);
	// 給 display 物件
	this->eventViewList = new Displayer();

	// 做一些 View

	// 右上的 View
	MySpace::ViewPtr monsterProperty = myutil::createView('*', 3, 20);
	monsterProperty->setLeftTop(100, 2);
	monsterProperty->print(2, "  Type: " + this->monster->getTypeStr());

	// 左上的 ASCII 圖，  (寵物在 console 的圖示)。
	MySpace::ViewPtr ascii = myutil::getMonsterASCIIViewPtrbyIdx(this->monster->getIdx());
	ascii->setLeftTop(1, 1);
	this->eventViewList->registerView(ascii);// 左上的 View

	// 玩家持有 monster列表的 View

	this->eventViewList->registerView(monsterProperty);// 右上的 View
}

// 遭遇到 monster 的實作
void EncounterMonsterEvent::touchOff(){
	// 遇到 怪拉ㄚㄚㄚㄚㄚ
	rlutil::cls();

	this->eventViewList->showRegisteredView();
	//this->monster

	rlutil::anykey("按下任意按鍵回到地圖...\n");
	rlutil::cls();
}
