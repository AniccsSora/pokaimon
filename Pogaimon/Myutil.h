#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Mydefine.h"
#include "rlutil.h"
#include "GameMap.h"
#include "Monster.h"
#include "MonsterProperty.h"

using std::cout;
using std::endl;

#define typeTablePath "./assets/type.csv"
#define asciiPath "./assets/icons/color/"

typedef MySpace::Vec_2D_<double> TypeTable;

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

	// 讀取 csv檔案 的 monster。製作成 屬性表，要建立 monster時 直接用這個物件即可參考各項數值。
	MonsterPropertyList inline loadMonsterFile();
	
	// 取得屬性攻擊倍率表~~
	TypeTable inline getDamageRatioTable();

	// 給 idx，送你 ASCII 2D vec。(他只幫你給 element 的內容而已)
	MySpace::ViewPtr inline getMonsterASCII(int monsterIdx);
	
}


void myutil::helloMother(){
		std::cout << "hello" << std::endl;
}

// 讀取 Map。不會印出 Map。
GameMapPtr myutil::loadMap(std::string filename)
{
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
		rlutil::setColor(rlutil::WHITE); // 白色
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
	else if ('#' == cube) {// # 建築入口, yellow,可以穿越
		rlutil::setColor(rlutil::YELLOW);
	}
	else {
		rlutil::setColor(rlutil::WHITE); // 白色
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
	int MAX_ROW = 40;
	int MAX_COL = 150;
	for (size_t row_idx = 0; row_idx < MAX_ROW; ++row_idx) {
		for (size_t col_idx = 0; col_idx < MAX_COL; ++col_idx) {
			if (row_idx == 0 || row_idx == MAX_ROW-1 ) { // first row
				std::cout << (col_idx + 1) % 10; // 只印出 數字...
				continue;
			}
			else { // not first row
				if (col_idx == 0) { // first item of row, but not first row.
					std::cout << (row_idx + 1) % 10; // 每行的第一個元素, 也只印數字。
					continue;
				}
				else { // not first item of row
					if (col_idx % 10 == 9) { // 印出 垂直分隔線。
						std::cout << '|'; continue;
					}
					else {
						if (row_idx % 10 == 9) { // 印出 水平分隔線。
							std::cout << '-'; continue;
						}
						else {
							std::cout << ' '; continue;
						}
					}
				}
			}
		}
		cout << endl;
	}
}

MonsterPropertyList myutil::loadMonsterFile()
{
	std::string line;
	std::ifstream pokemonsTableFile(monster_define_filePath);

	// 用指標傳回去
	MySpace::Vec_1D_<MonsterProperty*> *rtnList = new MySpace::Vec_1D_<MonsterProperty*>();

	if (pokemonsTableFile.is_open())
	{
		while (getline(pokemonsTableFile, line))
		{
			// 暫時存放用，這個物件不會被傳遞，我們只會參考其數值。
			std::vector<std::string> tmpList; 
			tmpList.reserve(8);// 一個怪物有8個屬性 相幫其初始化大小。

			// parse line(from csv)
			std::string delimiter = ",";

			// process each line, and use dilimiter to split it.
			size_t pos = 0;
			std::string token;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				//std::cout << token << std::endl;// 其他的 ability
				tmpList.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			// 最後一個 ability。(這個處理是會破壞 line 的所以可這樣取值)
			//std::cout << line << std::endl;
			tmpList.push_back(line);
			// End of parse line

			//int idx, std::string name, std::string type, int hp, int atk, int def, int speed, int ability
			// 建構 "怪物參數" 物件，一個怪物就是一個 "怪物參數"。(不想動腦了，請容忍這種建立法。XD)
			MonsterProperty *mpElement = new MonsterProperty(
				std::atoi(tmpList.at(0).c_str()),
				tmpList.at(1),
				tmpList.at(2),
				std::atoi(tmpList.at(3).c_str()),
				std::atoi(tmpList.at(4).c_str()),
				std::atoi(tmpList.at(5).c_str()),
				std::atoi(tmpList.at(6).c_str()),
				std::atoi(tmpList.at(7).c_str())
			);
			// std::cout << "One line process finish!" << std::endl;
			rtnList->push_back(mpElement);
		}
		pokemonsTableFile.close();
	}
	else {
		std::cout << "Unable to open file: " << "\"" << monster_define_filePath << "\"" << std::endl;
		system("pause");
		exit(887);
	}

	return *rtnList;
}

TypeTable myutil::getDamageRatioTable()
{
	
	std::string line;
	std::ifstream typeTableFile(typeTablePath);

	// 要回傳的 物件。
	TypeTable rtbTable;
	
	if (typeTableFile.is_open())
	{
		MySpace::Vec_1D_<double> vec_row_tmp;
		while (getline(typeTableFile, line))
		{
			vec_row_tmp.clear();
			
			// parse line(from csv)
			std::string delimiter = ",";

			// process each line, and use dilimiter to split it.
			size_t pos = 0;
			std::string token;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				token = line.substr(0, pos);
				//std::cout << token << std::endl;// 其他的 ability
				try {
					vec_row_tmp.push_back(std::atof(token.c_str())); // Exception
				}
				catch (...) {
					cout << "Exception : token = \"" << token.c_str() << "\"" << endl;
					std::system("pause");
					std::exit(777888);
				}
				line.erase(0, pos + delimiter.length());
			}
			try {
				// 注意 這是 line。 不是 token. 這邊用的 csv 解析 會破壞 line，故最後 line 會只剩下一個元素。
				vec_row_tmp.push_back(std::atof(line.c_str())); // Exception
			}
			catch (...) {
				cout << "Exception : token = \"" << token.c_str() << "\"" << endl;
				std::system("pause");
				std::exit(7778881);
			}
			// End of parse line
			rtbTable.push_back(vec_row_tmp);// save vector
			// GOTO next line
		}
		typeTableFile.close();
	}
	else {
		std::cout << "Unable to open file: " << "\"" << typeTablePath << "\"" << std::endl;
		system("pause");
		exit(887);
	}

	return rtbTable;
}

MySpace::ViewPtr myutil::getMonsterASCII(int monsterIdx)
{
	MySpace::ViewPtr rtnView = new MySpace::View();

	// 記錄著 View 的內容。
	// 整個View 的DATA，最後要被包去 View::element
	MySpace::Vec_2D_<char> element;

	// 讀檔~
	std::string line;

	// 補零用 "1" -> "001"。
	std::string file_name = std::string(3 - std::to_string(monsterIdx).length(), '0') + std::to_string(monsterIdx);
	// 拼出完整路徑 + 檔案名稱。
	std::string file_PTH_NAME = asciiPath + file_name + ".txt";
	std::ifstream asciifile(file_PTH_NAME);

	if (asciifile.is_open())
	{
		std::vector<char> vec_row_tmp;
		while (getline(asciifile, line))
		{
			vec_row_tmp.clear();
			// 處理 一行資料。
			for (size_t i = 0; i < line.length(); i++) {
				{
					vec_row_tmp.push_back(line[i]);
				}
			}
			element.push_back(vec_row_tmp);
			// GOTO next line
		}
		asciifile.close();
	}
	else {
		std::cout << "Unable to open file: " << "\"" << file_PTH_NAME << "\"" << std::endl;
	}

	// 是 ASCII image ??
	rtnView->isASCII = true;
	// 塞回去~
	rtnView->element = element;

	return rtnView;
}

