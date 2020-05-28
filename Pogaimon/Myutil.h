#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Mydefine.h"
#include "rlutil.h"
#include "GameMap.h"
using std::cout;
using std::endl;



namespace myutil {
	//測試  // inline can resolve error LNK2005
	void inline helloMother(); 

	// 讀取 Map，並show在終端， ** 這個會 new 指標 請注意要 DELETE **
    GameMapPtr inline loadMap(std::string filename);

    // 請使用者校正 console。
    void inline correctionConsole();

	// 允許玩家移動並依照 map 的邏輯去限制移動範圍
	// void inline playerService();
    // 在螢幕下方添加 log。 one line only。
    void inline update_log(std::string msg);

	// 印出 cube
	// 他會依照定義的顏色來印出 cube字元。如果 x= -1, y= -1 代表不指定 locate
	void inline printCube(int x,int y, char cube);
}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
}

// 讀取 Map，並show在終端
GameMapPtr myutil::loadMap(std::string filename)
{
    std::string line; // 每行的 tmp
    std::ifstream mapfile(filename);
    
    if (mapfile.is_open())
    {
        while (getline(mapfile, line))
        {
            // 處理 一行資料。
            for (size_t i = 0; i < line.length(); i++) {
				printCube(-1, -1, line[i]); // -1 代表不指定 locate
            }cout << "\n";
            // GOTO next line
        }
        mapfile.close();
    }
    else { 
        std::cout << "Unable to open file: " << "\"" << filename << "\"" << std::endl;
    }
    return new GameMap(filename);
}



void myutil::correctionConsole()
{
    using std::cout;
    using std::endl;
    cout << "*************************************************"\
         << "**************************************************" << endl;
    for (int i = 0; i < 31; i++) {
        cout << "*";
        for (int i = 0; i < 97; i++) {
            cout << " ";
        } cout << "*" << endl;
    }
    cout << "*************************************************"\
        << "**************************************************" << endl;

    cout << "Please make \"****\" line to be \"retangle\"." << endl;
    rlutil::anykey("\n\nPress any key to continue...\n");
    rlutil::cls();
}

// 允許玩家移動並依照 map 的邏輯去限制移動範圍
// void inline playerService();
// 在螢幕下方添加 log。 one line only。
void myutil::update_log(std::string msg)
{
    rlutil::locate(1, 32);
    cout << "\r" << std::string(40,' ')<< endl;// 填入40個 空白
    rlutil::locate(1, 32);
    cout << "\rlog: "<<msg << endl;
}

void myutil::printCube(int x, int y, char cube)
{
	// 先記錄 預設的顏色，不用 handle 變數沒關係。
	rlutil::saveDefaultColor();

	// 定位 游標
	if (x != -1 && y != -1){ rlutil::locate(x, y); }
	
	if ('*' == cube) {// * 牆壁,無法穿越
		// 原色
	}
	else if (';' == cube) {//; 草地, green,可以穿越
		rlutil::setColor(rlutil::GREEN);
	}
	else if ('!' == cube) {// ! 樹木, brown,無法穿越
		rlutil::setColor(rlutil::BROWN);
	}
	else if ('~' == cube) {// ~ 水池, blue,可以穿越
		rlutil::setColor(rlutil::BLUE);
	}
	/*else if (' ' == line[i]) {
		// another~~
	}*/
	else if ('#' == cube) {// # 建築入口, yellow,可以穿越
		rlutil::setColor(rlutil::YELLOW);
	}
	cout << cube;
	rlutil::resetColor();
}

