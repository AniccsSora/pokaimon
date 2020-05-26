/**
 * File: test.cpp
 *
 * About: Description
 * This is a C++ example / test program for rlutil that can be
 * used for validating or showcasing the functionality.
 *
 * About: Copyright
 * (C) 2010 Tapio Vierros
 *
 * About: Licensing
 * See <License>
 */

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
	// 
    GameMap map = myutil::loadMap("../Pogaimon/assets/yzumap.txt");

	// 原點 hardcode
	int x = 20; int y = 30;
	rlutil::locate(x, y);
	cout << "@" << endl;
	while (1) {
		
		rlutil::hidecursor();
		rlutil::locate(x, y); 
		cout << '@' << endl; // Output player
		while (true) {
			if (kbhit()) {
				char k = getch(); // Get character
				rlutil::locate(x, y); std::cout << " "; // Erase player
				if (k == arrow_Left) --x;
				else if (k == arrow_Right) ++x;
				else if (k == arrow_Up) --y;
				else if (k == arrow_Down) ++y;
				else if (k == ' ') break;
				rlutil::locate(x, y); std::cout << '@'; // Output player
			}
			std::cout.flush();
		}
		rlutil::showcursor();
	}


	// 回到最新行數
	//rlutil::locate(1, 32);
	return 0;
}
