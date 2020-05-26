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
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>


#define waitkey rlutil::anykey("Press any key to continue...\n")

char chargen() {
	return rand() % (('~' - '!') + 1) + '!'; // I am really sorry for this
}

int main() {
    // 跟 resetColor() 有關係。
    // 呼叫 resetColor()，可以 回到 saveDefaultColor() 當時所記錄的顏色。
	//rlutil::saveDefaultColor();

	myutil::helloMother();

	// Test 9
	int x = 7; int y = 7;
	rlutil::cls();
	rlutil::CursorHider curs;
	std::cout << "Test 9: Arrow keys" << std::endl;
	std::cout << "You should be able to move the '@' character with arrow keys." << std::endl;
	std::cout << "Hit Escape to continue to the next test." << std::endl;
	gotoxy(x, y); std::cout << '@' << std::endl; // Output player
	while (true) {
		if (kbhit()) {
			int k = rlutil::getkey(); // Get character
			gotoxy(x, y); std::cout << " "; // Erase player
			if (k == rlutil::KEY_LEFT) --x;
			else if (k == rlutil::KEY_RIGHT) ++x;
			else if (k == rlutil::KEY_UP) --y;
			else if (k == rlutil::KEY_DOWN) ++y;
			else if (k == rlutil::KEY_ESCAPE) break;
			gotoxy(x, y); std::cout << '@'; // Output player
			std::cout.flush();
		}
	}
	
	
	return 0;
}
