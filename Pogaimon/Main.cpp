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
    // �� resetColor() �����Y�C
    // �I�s resetColor()�A�i�H �^�� saveDefaultColor() ��ɩҰO�����C��C
	//rlutil::saveDefaultColor();

    myutil::correctionConsole();
    myutil::loadMap("../Pogaimon/assets/yzumap.txt");

	
	
	
	return 0;
}
