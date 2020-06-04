#include "Event.h"



// 建構子
EncounterMonsterEvent::EncounterMonsterEvent(MonsterPropertyList mstPropertyList,Player* servicedPlayer):Event(){
	// 隨便生一個怪物~~
	this->encounterMonster = new Monster(rand(), mstPropertyList);
	
	// 給 display 物件
	this->eventViewList = new Displayer();

	// 所服務的玩家
	this->servicedPlayer = servicedPlayer;

	// log 內容的 View。
	//log_content_view = 最後面再加入;

	// 做一些 View
	//=============================================================================

	//  寵物屬性的 View
	MySpace::ViewPtr monsterProperty = myutil::createView('*', 15, 40);
	monsterProperty->setLeftTop(80, 2);
	
	monsterProperty->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
	monsterProperty->print(4, " ************************************ ");
	monsterProperty->print(5, "  Index - : " + std::to_string(this->encounterMonster->getIdx()));
	monsterProperty->print(6, "  Name -- : " + this->encounterMonster->getName());
	monsterProperty->print(7, "  Type -- : " + this->encounterMonster->getTypeStr());
	monsterProperty->print(8, "  HP ---- : " + std::to_string(this->encounterMonster->getHp()));
	monsterProperty->print(9, "  ATK --- : " + std::to_string(this->encounterMonster->getAtk()));
	monsterProperty->print(10, "  DEF --- : " + std::to_string(this->encounterMonster->getDef()));
	monsterProperty->print(11, "  SPEED - : " + std::to_string(this->encounterMonster->getSpeed()));
	monsterProperty->print(12, "  Ability : " + this->encounterMonster->getAbilityNameByAbliIdx( this->encounterMonster->getAbilityIdx()));
	this->eventViewList->registerView(monsterProperty);// 寵物屬性 的 View
	//=============================================================================

	//  ASCII 圖  (寵物在 console 的圖示)。
	MySpace::ViewPtr ascii = myutil::getMonsterASCIIViewPtrbyIdx(this->encounterMonster->getIdx());
	ascii->setLeftTop(1, 1);
	this->eventViewList->registerView(ascii);//  ASCII圖 的 View
	//=============================================================================
	short logger_w = 40, MostleftTop_Y = 31;// for log view
	short MostleftTop_X = 80;// for log view, Player.cpp::addMonster() 會使用此數值(不是變數)。
	short title_H = 3, content_H = 7;// for log view
	short holdMonsterView_Y = 20;// for monater, Player.cpp::addMonster() 會使用此數值(不是變數)。
	//=============================================================================
	// 玩家持有 monster View
	// map 上的 view 位置跟這個不一樣，但我不想要管太多乾脆複製一個來改位置就可以很舒服了
	MySpace::View* src = servicedPlayer->getHoldMonsterView();
	MySpace::View* copied_Player_Hole_Monster_View = new MySpace::View(*src);
	// 玩家持有 monster View
	copied_Player_Hole_Monster_View->setLeftTop(MostleftTop_X, holdMonsterView_Y); // 
	copied_Player_Hole_Monster_View->setframeColor(rlutil::LIGHTBLUE);
	this->eventViewList->registerView(copied_Player_Hole_Monster_View);// 持有怪物的 View。
	//=============================================================================
	// 提示訊息 View Title
	MySpace::ViewPtr loggerTitle = myutil::createView('L', title_H, logger_w); // 標題區域 把這兩個 View 拼起來(視覺上成為一個View)。
	loggerTitle->setLeftTop(MostleftTop_X, MostleftTop_Y);
	int speceSize = 13;
	loggerTitle->print(2, std::string(speceSize, ' ')+"~~ Message ~~"+std::string(speceSize,' '));
	loggerTitle->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(loggerTitle);//log View Title

	// 提示訊息 View Content
	MySpace::ViewPtr logger = myutil::createView('L', content_H, logger_w);
	logger->setLeftTop(MostleftTop_X, MostleftTop_Y + content_H- title_H);
	logger->print(2, "  Press \"SPACE\" to return to the map. ");
	logger->print(4, "  Press \" C \" try catch monster.");
	logger->print(6, "  >");
	logger->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(logger);// log View Content
	// 更新 Event 要用的。
	this->log_content_view = logger;
	//=============================================================================

	// 創立 View <End>
	
}

// 遭遇到 monster 的實作
void EncounterMonsterEvent::touchOff(){
	// 遇到 怪拉ㄚㄚㄚㄚㄚ
	// this->encounterMonster;
	
	
	rlutil::cls();

	this->eventViewList->showRegisteredView();
	
	//this->monster
	rlutil::locate(84, 41);
	rlutil::showcursor();

	while (true) {
		if (kbhit()) {
			// 偵測鍵盤
			char k = getch(); // Get character
			if (k == 'C' || k == 'c') { 
				rlutil::hidecursor();
				if (this->servicedPlayer->getMonsterListSize() < 3) {
					cout << "  Start Catch-> " + this->encounterMonster->getName();
					rlutil::msleep(500);
				}
				else { // Hardcode 修改 Message View 的訊息。 就是這麼難看XD。
					int view_x_ptr, view_y_ptr;
					view_x_ptr = this->log_content_view->status.lefttop.x+1; 
					view_y_ptr = this->log_content_view->status.lefttop.y + 2;//
					rlutil::locate(view_x_ptr, view_y_ptr);//locate到 第一行 開頭位置
					cout << std::string(40, ' ');//清空該區
					rlutil::locate(view_x_ptr, view_y_ptr);//再次回到 第一行 開頭位置，此時是空白的。
					cout << std::string("  Press \"ESC\" to abort the crawl.");
					// 接下來去改第二行 msg "Press " C " try catch..."
					// logger->print(4, "  Press \" C \" try catch monster.");
					rlutil::locate(view_x_ptr, view_y_ptr+2);//到 第二行 開頭位置
					cout << std::string(40, ' '); //清空該區
					rlutil::locate(view_x_ptr, view_y_ptr + 2);//回到 第二行 開頭位置
					cout << std::string("  Press \" R \" to replace the monster.");

					rlutil::saveDefaultColor();
					rlutil::setColor(rlutil::LIGHTRED);
					rlutil::locate(view_x_ptr+4, view_y_ptr + 4);//到 第三行 開頭位置
					cout << "Use the \'W\',\'S\' buttons to replace.";
					rlutil::resetColor();
				}
				this->servicedPlayer->addMonster(this->encounterMonster); // 會作 大於 3的檢查
				
				break;
			}
			else if (k == ' ') { 
				this->log_content_view->print(6, "  Cancel catch...");
				rlutil::locate(84, 41); //harcode.
				cout << "  Cancel catch...";
				//this->eventViewList->showRegisteredView();// 改個字 整圖重印...// 消耗過多效能
				rlutil::hidecursor();
				rlutil::msleep(500);
				break; 
			}
		}
		std::cout.flush();
	}
	rlutil::cls();
}

EncounterNPCEvent::EncounterNPCEvent(Player* player, PlayerPtr encounterNpc)
{
	// 初始化
	this->player = player;
	this->encounterNpc = encounterNpc;
}

void EncounterNPCEvent::touchOff(){
	Jym *myJJ = new Jym(player, encounterNpc); // TODO: 要記得刪掉。
	myJJ->battle_start();
}
