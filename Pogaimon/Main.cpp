#include "rlutil.h"
#include "Myutil.h"
#include "GameMap.h"
#include "Player.h"
#include "Displayer.h"
#include "InfoProvider.h"
#include "Monster.h"
#include "GameService.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>



#define waitkey rlutil::anykey("Press any key to continue...\n")
// 用方向鍵 程式會怪怪的。。
constexpr auto arrow_Left = 75;
constexpr auto arrow_Up = 72;
constexpr auto arrow_Down = 80;
constexpr auto arrow_Right = 77;

char chargen() {
	return rand() % (('~' - '!') + 1) + '!'; // I am really sorry for this
}

int main() {
	srand(time(NULL));
	//================ test~~
	while (0) {
		// 取得寵物參數圖鑑
		//MonsterPropertyList mstPropertyList = myutil::loadMonsterFile();
		//// 取得相剋表
		//TypeTable typeTable = myutil::getDamageRatioTable();

		//int idx = 1;
		//MonsterPtr DAJJ = new Monster(rand(), mstPropertyList);
		//MonsterPtr DAGG = new Monster(rand(), mstPropertyList);

		//cout << typeTable.at(DAJJ->getType()).at(DAGG->getType()) << endl;
		//MySpace::ViewPtr ascii =  myutil::getMonsterASCII(5);
		
		rlutil::anykey("test end...");
	}
	//================
	rlutil::saveDefaultColor();
	//myutil::screen_ruler(); waitkey;

	// 初始化 一些物件，地圖、玩家、遊戲輔助類別(滿多的)...
	//===============
	// 取得MAP物件，用來檢驗碰狀事件，loadMap 會傳回 *map。
	GameMapPtr map = myutil::loadMap("../Pogaimon/assets/yzumap.txt");

	// 玩家站立原點, hardcode
	int x = 15; int y = 18; // 20, 30

	// 建立玩家, 給名字 給生成座標。
	Player* tony = new Player("tony", x, y);

	// 控制 console 內 View 的顯示。
	Displayer viewManager;

	// 設定一些View... 
	MySpace::ViewPtr ascii = myutil::getMonsterASCIIViewPtrbyIdx(5); //小火龍
	ascii->setLeftTop(100, 50);
	//viewManager.registerView(ascii);

	// log 區域。
	MySpace::ViewPtr log_Window = myutil::createView('*', 5, 60); // 決定 View 的大小
	log_Window->setLeftTop(65, 23); // 決定 這個View 的位置
	log_Window->setframeColor(rlutil::GREEN);
	viewManager.registerView(log_Window);// 將想要被顯示的 View 註冊進 Displayer 管理。

	// 顯示玩家持有寵物用的 View
	//MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 30);
	//monsterHold_Window->setframeColor(rlutil::YELLOW); // 邊框顏色
	//monsterHold_Window->setLeftTop(100, 6); // 決定 這個View 的位置
	//viewManager.registerView(monsterHold_Window);// 將想要被顯示的 View 註冊進 Displayer 管理。
	//monsterHold_Window->print(1, "  === Player Monster === ");
	//monsterHold_Window->print(3, "  1. None");
	//monsterHold_Window->print(5, "  2. None");
	//monsterHold_Window->print(7, "  3. None");

	// 決定 玩家 monster View 的位置, 顏色是在建構時給定的。
	tony->setMonsterView_FT(100, 6);
	// 將想要被顯示的 View 註冊進 Displayer 管理。
	viewManager.registerView(tony->getHoldMonsterView());

	// 玩家 info 提供類別, 會負責回傳一些 log(std::string).
	InfoProvider tonyInfoService(tony, map);

	// 可以服務 玩家  的咚咚物件。(只要一個就可以了)。
	GameService gameService(map);
	
	//=============== 初始化完畢
	
	while (1) {
		
		// 隱藏游標
		rlutil::hidecursor();

		// 放置玩家
		// map->movePlayer( tony, x, y);

		// 紀錄位置
		x = tony->getPlayerPosition().x;
		y = tony->getPlayerPosition().y;

		// 印出 地圖，會附帶顏色變化
		map->showMap_and_Player(*tony);

		// 對指定的 View 給定 訊息。
		log_Window->print(1, tonyInfoService.getPlayerPositionMsg());
		log_Window->print(3, " Bush Event = ");

		// 印出 Displayer 所管理的 view物件。
		viewManager.showRegisteredView();

		// Player move 控制 以及各處發事件
		{
			while (true) {
				rlutil::hidecursor();
				if (kbhit()) {
					// 偵測鍵盤
					char k = getch(); // Get character
					if (k == 'a') { --x; }
					else if (k == 'd') { ++x; }
					else if (k == 'w') { --y; }
					else if (k == 's') { ++y; }
					else if (k == ' ') { break; }
					// 放置玩家
					map->movePlayer(tony, x, y);
					// 紀錄位置
					x = tony->getPlayerPosition().x; y = tony->getPlayerPosition().y;
					
					// 如果玩家站的不是空 字元。
					if (' ' != map->returnCubeBy(x,y)
						//&& myutil::X_Probability_get_True(0.1)
						){
						// 由 gameService 回報玩家現在的 Event
						// gameService 上方 new 出時必須要帶 map(copy的) 進去 因為他必須要參考玩家位置
						Event* tonyEvent = gameService.getEvent(tony);
						// 這個 event get 到時 他回傳的 Event 就要把 這個 event 所擁有的東西 都給訂好， view等 一些設定。
						// Event 
						tonyEvent->touchOff(); //觸發該 event，並且 evnet 會有 touchOff() 一定會刷掉螢幕，他會把畫面先刷掉。
						delete[] tonyEvent;
					}// 特殊格 判斷完畢。

					// 返回地圖 畫面
					map->showMap_and_Player(*tony);

					// show log 基本上debug 用。
					// 對指定的 View 給定 訊息。
					log_Window->print(1,tonyInfoService.getPlayerPositionMsg()); 
					log_Window->print(3, " NPC IDX = " + std::to_string(map->return_NPC_idx(x,y)));

					// 印出 Displayer 所管理的 view物件。
					viewManager.showRegisteredView();
				}
				std::cout.flush();
			}// break 控制玩家;

			// 下面處理 戰鬥???
		}
	}
	return 0;
}
