#include "rlutil.h"
#include "Myutil.h"
#include "GameMap.h"
#include "Player.h"
#include "Displayer.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>


#define waitkey rlutil::anykey("Press any key to continue...\n")
constexpr auto arrow_Left = 75;
constexpr auto arrow_Up = 72;
constexpr auto arrow_Down = 80;
constexpr auto arrow_Right = 77;

char chargen() {
	return rand() % (('~' - '!') + 1) + '!'; // I am really sorry for this
}

int main() {
	{
		// 跟 resetColor() 有關係。
		// 呼叫 resetColor()，可以 回到 saveDefaultColor() 當時所記錄的顏色。
		//rlutil::saveDefaultColor();
	}

    //myutil::correctionConsole();
	// 取得MAP物件，用來檢驗碰狀事件，loadMap 會把 map 印在 console。
    GameMapPtr map = myutil::loadMap("../Pogaimon/assets/yzumap.txt");

	// 原點 hardcode
	int x = 20; int y = 30;

	// 建立玩家
	Player *tony = new Player("tony", x, y);
	/*rlutil::locate(x, y);
	cout << tony->getNotation() << endl;*/

	// 控制console 內 View 用的。
	Displayer viewManager; 
	// 
	MySpace::View testView = myutil::createView('*', 5, 20);
	//testView.setframeColor(rlutil::GREEN);

	// log 區域。
	MySpace::View log_Window = myutil::createView('*', 5, 60);
	log_Window.setLeftTop(65,23);
	

	// 將想要被顯示的 View 註冊進 Displayer 管理。
	viewManager.registerView(log_Window);
	
	while (1) {

		// 隱藏游標
		rlutil::hidecursor();
		// 放置玩家
		map->movePlayer( tony, x, y);
		// 紀錄位置
		x = tony->getPlayerPosition().x;
		y = tony->getPlayerPosition().y;
		
		// Player move 控制 以及各處發事件
		{
			// 印出 地圖，會附帶顏色變化
			map->showMap_and_Player(*tony);
			while (true) {
				if (kbhit()) {
					// 偵測鍵盤
					char k = getch(); // Get character
					if (k == arrow_Left) { --x; }
					else if (k == arrow_Right) { ++x; }
					else if (k == arrow_Up) { --y; }
					else if (k == arrow_Down) { ++y; }
					else if (k == ' ') { break; }
					// 放置玩家
					map->movePlayer(tony, x, y);
					// 紀錄位置
					x = tony->getPlayerPosition().x;
					y = tony->getPlayerPosition().y;
					// shoe log
					rlutil::locate(1, 35);

					std::string pos_msg = "玩家位置 : x: " + std::to_string(tony->getPlayerPosition().x) +
						", y: " + std::to_string(tony->getPlayerPosition().y) +
						", 站立cube = \"" + map->returnCubeBy(x, y) + "\"\n";

					log_Window.print(1, pos_msg);

					//viewManager.showRegisteredView();
					viewManager.showView(log_Window);
				}
				std::cout.flush();
			}// break;
			
			rlutil::cls();
			// 印出 view 的物件。
			
			map->showMap_and_Player(*tony);
			viewManager.showView(testView,100,30);
			
			rlutil::anykey();
		}
	}
	return 0;
}
