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

	// 玩家持有 monster列表的 View<Start>
	short logger_w = 40, MostleftTop_X = 80, MostleftTop_Y = 20;
	short title_H = 3, content_H = 7;

	// 提示訊息 View Title
	MySpace::ViewPtr loggerTitle = myutil::createView('L', title_H, logger_w); // 標題區域 把這兩個 View 拼起來(視覺上成為一個View)。
	loggerTitle->setLeftTop(MostleftTop_X, MostleftTop_Y);
	int speceSize = 13;
	loggerTitle->print(2, std::string(speceSize, ' ')+"~~ 提示訊息 ~~"+std::string(speceSize,' '));
	loggerTitle->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(loggerTitle);// 左上的 View Title

	// 提示訊息 View Content
	MySpace::ViewPtr logger = myutil::createView('L', content_H, logger_w);
	logger->setLeftTop(MostleftTop_X, MostleftTop_Y + content_H- title_H);
	logger->print(2, "  按下 空白鍵 回到地圖... ");
	logger->print(4, "  按下 \" C \" 開始捕捉...");
	logger->print(6, "  其他訊息~~~~~          ");
	logger->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(logger);// 左上的 View
	// 玩家持有 monster列表的 View <End>

	this->eventViewList->registerView(monsterProperty);// 右上的 View
}

// 遭遇到 monster 的實作
void EncounterMonsterEvent::touchOff(){
	// 遇到 怪拉ㄚㄚㄚㄚㄚ
	rlutil::cls();

	this->eventViewList->showRegisteredView();
	//this->monster

	while (true) {
		if (kbhit()) {
			// 偵測鍵盤
			char k = getch(); // Get character
			if (k == 'C' || k == 'c') { 
				std::cout << "開始捕捉...\n";
				rlutil::anykey();
				break;
			}
			else if (k == ' ') { break; }
		}
		std::cout.flush();
	}
	rlutil::cls();
}
