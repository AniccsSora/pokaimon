#include "rlutil.h"
#include "Myutil.h"
#include "Player.h"
#include "GameMap.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>



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
    GameMap map = myutil::loadMap("../Pogaimon/assets/yzumap.txt");

	// 原點 hardcode
	int x = 20; int y = 30;

	// 建立玩家
	Player *tony = new Player("tony", x, y);
	/*rlutil::locate(x, y);
	cout << tony->getNotation() << endl;*/
	while (1) {

		// 隱藏游標
		rlutil::hidecursor();
		// 放置玩家
		map.movePlayer( *tony, x, y);
		// 紀錄位置
		x = tony->getPlayerPosition().x;
		y = tony->getPlayerPosition().y;
		
		
		while (true) {
			if (kbhit()) {
				char k = getch(); // Get character
				if (k == arrow_Left) {--x;}
				else if (k == arrow_Right) {++x;}
				else if (k == arrow_Up) {--y;}
				else if (k == arrow_Down) {++y;}
				else if (k == ' ') { break; }
				// 放置玩家
				map.movePlayer(*tony, x, y);
				// 紀錄位置
				x = tony->getPlayerPosition().x;
				y = tony->getPlayerPosition().y;
				rlutil::locate(1, 35);
				cout << "玩家位置 : x: " << tony->getPlayerPosition().x
					<< ", y: " << tony->getPlayerPosition().y
					<< ", 站立cube = \"" << map.returnCubeBy(x, y) << "\"" << endl;
				//rlutil::locate(x, y); std::cout << '@'; // Output player
			}
			std::cout.flush();
		}
		
	}


	// 回到最新行數
	//rlutil::locate(1, 32);
	return 0;
}
