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

	// 應該不會被程式使用... 沒機會用到XD
	MySpace::View inline createViewByFile(std::string filename, std::string viewName);

	// View 就是一個由 某個 符號圍成的區域，會提供 可印出座標有幾行，最大長度支援到多少。
	// row 可以寫幾行字。
	// column 一行可以寫多少字。
	// default color : 白。
	MySpace::ViewPtr inline createView(char style,short row, short column);

	// 在終端機 印出 尺標 助於 版面配置
	void inline screen_ruler();
}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
}

// 讀取 Map。不會印出 Map 了
GameMapPtr myutil::loadMap(std::string filename)
{
	//std::string line; // 每行的 tmp
    //std::ifstream mapfile(filename);
    //
    //if (mapfile.is_open())
    //{
    //    while (getline(mapfile, line))
    //    {
    //        // 處理 一行資料。
    //        for (size_t i = 0; i < line.length(); i++) {
				//printCube(-1, -1, line[i]); // -1 代表不指定 locate
    //        }cout << "\n";
    //        // GOTO next line
    //    }
    //    mapfile.close();
    //}
    //else { 
    //    std::cout << "Unable to open file: " << "\"" << filename << "\"" << std::endl;
    //}
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

// 在螢幕下方添加 log。 one line only。 FOR DEBUG
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

MySpace::View myutil::createViewByFile(std::string filename, std::string viewName)
{
	// 拿來放 字元 資料。
	MySpace::Vec_2D_<char> viewData;
	MySpace::Vec_1D_<char> singleLineTmp; // 一行的 data tmp

	std::string line; // 每行的 tmp
	std::ifstream viewfile(filename);

	short max_length_of_row = 0;
	if (viewfile.is_open())
	{
		while (getline(viewfile, line))
		{
			// 處理 一行資料。
			for (size_t i = 0; i < line.length(); i++) {
				singleLineTmp.push_back(line[i]);
			}cout << "\n";
			// 更新最大長度
			if ( (short)singleLineTmp.size() > max_length_of_row) {
				max_length_of_row = (short)singleLineTmp.size();
			}
			viewData.push_back(singleLineTmp);
			// GOTO next line
		}
		viewfile.close();
	}
	else {
		std::cout << "Unable to open file: " << "\"" << filename << "\"" << std::endl;
	}

	// ViewStatus 資料結構。
	MySpace::ViewStatus status;
	// 現在還無法給定 此 view 的 印出基準點。
	status.lefttop.x = -1;
	status.lefttop.y = -1;
	// view 的長寬
	status.size_w_h.w = max_length_of_row;
	status.size_w_h.h = (short)viewData.size();

	// 開始組合 View 資料結構
	MySpace::View thisView;
	thisView.element = viewData;
	thisView.status = status;
	thisView.viewName = viewName;

	return thisView;
}


MySpace::ViewPtr myutil::createView(char style, short rowSize, short columnSize)
{
	// 宣告個 View 最後回傳
	MySpace::ViewPtr rtnView = new MySpace::View();

	// View 是會被多 "圍"一圈。 所以要各加上2。 hard code。寫死
	rowSize += 2;
	columnSize += 2;
	
	// 整個View 的DATA，最後要被包去 View::element. 並 初始化 vector 大小。
	MySpace::Vec_2D_<char> element(rowSize);

	for (size_t i=0; i < rowSize; ++i) {
		//rowBuffer.clear();
		for (size_t j=0; j < columnSize; ++j) {
			if (i == 0 || i == rowSize-1) {// "描"出邊框(上 && 下)。
				element.at(i).push_back(style);
				continue;
			}
			if (j == 0 || j == columnSize-1) {
				element.at(i).push_back(style);
				continue;
			}
			// 其餘判定為 content area(代表可以填入 自己像要資料的部分。)
			element.at(i).push_back(' ');
			continue;
		}// One row data complete.
	}

	// 整個 View結構 (參數包裹)。
	MySpace::ViewStatus status;

	// 因為不知道他的座標 所以不設定。
	//status.lefttop = ???;

	// View 整體的 高x寬 (注意: 跟 可以打印 msg 的區域大小不同)
	status.size_w_h.h = rowSize;
	status.size_w_h.w = columnSize;

	//打包 rtnView
	rtnView->element = element;
	rtnView->status = status;
	
	return rtnView;
}

void myutil::screen_ruler()
{
}

