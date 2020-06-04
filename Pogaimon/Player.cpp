#include "Player.h"
#include "Mydefine.h"
#include "GameMap.h"
#include "Myutil.h"
#include <cctype>
#include <iostream>

Player::Player(std::string name, int x, int y)
{
	playerName = name;
	position.x = x;
	position.y = y;

	// 初始化一下此玩家 的 holdmonster View。
	MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 40);
	monsterHold_Window->setframeColor(rlutil::YELLOW); // 邊框顏色
	// monsterHold_Window->setLeftTop(100, 6); // 決定 這個View 的位置
	monsterHold_Window->print(1, "  === Player's Monster === ");
	monsterHold_Window->print(3, "  1. None");
	monsterHold_Window->print(5, "  2. None");
	monsterHold_Window->print(7, "  3. None");
	// 賦予 player物件 初始化的 View。
	this->monsterView = monsterHold_Window;
}

MySpace::Coordi Player::getPlayerPosition()
{
	return position;
}

char Player::getNotation()
{
	return notation;
}

void Player::setPosition(MySpace::Coordi newPosition)
{
	position = newPosition;
}

std::string Player::getName()
{
	return playerName;
}


void Player::showMe_by_coord()
{
	rlutil::setColor(getColor());
	rlutil::locate(position.x, position.y);
	std::cout << notation;
}

void Player::setColor(rlutil_Color c)
{
	color = c;
}

rlutil_Color Player::getColor()
{
	return color;
}

MySpace::ViewPtr Player::getHoldMonsterView()
{
	// 建構時就有了 沒必要再次重建。
	//// 如果根本沒有 View 被指派到這個 玩家物件身上。
	//if (this->monsterView == NULL) { // 幫玩家新增 View
	//	MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 30);
	//	monsterHold_Window->setframeColor(rlutil::YELLOW); // 邊框顏色
	//	// monsterHold_Window->setLeftTop(100, 6); // 暫不決定
	//	monsterHold_Window->print(1, "  === Player Monster === ");
	//	monsterHold_Window->print(3, "  1. None");
	//	monsterHold_Window->print(5, "  2. None");
	//	monsterHold_Window->print(7, "  3. None");

	//	this->monsterView = monsterHold_Window;
	//}

	return this->monsterView;
}

void Player::setMonsterView_FT(int x, int y)
{ 
	this->monsterView->setLeftTop(x, y);
}

// 超過三個怎麼辦?
void Player::addMonster(MonsterPtr monsterCaught) throw(OverThreeMonsterUNHANDLE)
{
	// monsterList、monsterView

	if (this->monsterList.size() >= 3) {
		int last_x = -1, last_y;
		int x = -1, y = -1; // console 游標定位用。
		// TODO : 要讓玩家可以選擇要汰換哪一隻 Monster.
		/*cout << " Over than three monster\n";
		throw OverThreeMonsterUNHANDLE("TODO : 要讓玩家可以選擇要汰換哪一隻 Monster.");*/

		// 游標 跳到 player monster View 的 第一行(1-base:4) 的最尾端 (基本上 monsterList 跟 monsterView 的數值要一樣)
		int locate_View_X_idx = -1; // 以此 View的LF為基準，我們要locate 的 X 位置。
		char previous_char = ' ';// 紀錄上一個 char
		
		// 應該是 monster View 某 element(列) 的資料
		MySpace::Vec_1D_<char> target_row = this->monsterView->element[3];
		if (target_row.size() > 0) {
			int row_size = target_row.size();
			for (size_t idx = 1; idx < row_size; ++idx) { // 走訪 該 row 元素，定位最後一個字.(idx=1是因為有邊框)
				const char this_char = target_row.at(idx);// 紀錄目前走到的 idx.
				if (isalpha(previous_char) && isspace(this_char)) {// 當前一個是字母 且 此位置是空白
					locate_View_X_idx = idx;
					break;
				}
				previous_char = this_char;
			}
			// 預防 跑完迴圈(locate_View_X_idx)還是爆炸。
			if (locate_View_X_idx < 0) { throw OverThreeMonsterUNHANDLE(" Err: locate_View_X_idx still < 0.");  }
			else { // 定位成功
				//要把 View 的 相對座標，傳換成全域(console 的 x,y)
				int MostleftTop_X = 80, holdMonsterView_Y = 23; // Console座標，hardcode from "Event.cpp"
				x = MostleftTop_X + locate_View_X_idx;
				y = holdMonsterView_Y;
				rlutil::locate(x, y); // 游標跳躍完成
				//rlutil::showcursor();
			}

		}else { throw OverThreeMonsterUNHANDLE(" Err: 第一行的 monster 訊息size() < 0"); }

		std::vector<int> canLocate_Y = { y , y + 2 , y + 4 }; // 指標用
		int canLocate_Y_idx = 0;
		x += 5;// 位移一下座標。 (很可能爆炸)
		// 監聽鍵盤 上下 要可以移動 1~3 區域 其他 Esc (X)返回，空白 替換。(3,5,7)1-base
		std::string lock_msg = " <- Replace this."; //游標 的資訊
		rlutil::locate(x, canLocate_Y[canLocate_Y_idx]);
		rlutil::saveDefaultColor();
		rlutil::setColor(rlutil::GREEN);
		std::cout << lock_msg; //  印出 "游標"
		rlutil::resetColor();
		while (true) {
			rlutil::hidecursor();
			if (kbhit()) {
				// 偵測鍵盤
				last_y = canLocate_Y[canLocate_Y_idx]; // 紀錄上次 y
				char k = getch(); // Get character
				if (k == 'w'||k=='W') { 
					--canLocate_Y_idx; 
					canLocate_Y_idx += 3;
					canLocate_Y_idx %= 3; 
				}
				else if (k == 's'|| k=='S') {  
					++canLocate_Y_idx; 
					canLocate_Y_idx += 3;
					canLocate_Y_idx %= 3;
				}
				else if ( 'r' == k || 'R' == k) {
					// 替換 monster List 的元素
					this->monsterList.at(canLocate_Y_idx);
					// 更新了資料 View 也要更新
					// 0 1 2  -> 3 5 7 (idx 對應 View 的實際列數)
					// 更新 View 的 內容
					std::string ms_name = "  " + std::to_string(canLocate_Y_idx + 1) + ". " + monsterCaught->getName();
					this->monsterView->print(3 + (canLocate_Y_idx * 2), ms_name);
					break;
				}
				else if ( 27 == k) { // ESC
					break; 
				}
				rlutil::locate(x, last_y);// 改變座標
				
				std::cout << std::string(lock_msg.size(),' '); //  清除 "游標" 
				rlutil::locate(x, canLocate_Y[canLocate_Y_idx]);// 改變座標
				rlutil::saveDefaultColor();
				rlutil::setColor(rlutil::GREEN);
				std::cout << lock_msg; //  印出 "游標"
				rlutil::resetColor();
			}
			std::cout.flush();
		}


		// 把指定的 Monster 先 delete 之後替換 至 目前要抓的 monster。
	}
	else { // 順序加入 至 monster list
		// Add monster to list.
		this->monsterList.push_back(monsterCaught);

		// 取得現在 monsterList 最大 idx。
		int idx = this->monsterList.size()-1;

		// Add View
		// 根據 hardcode : 怪獸可印行為 3, 5, 7。

		// 格式大概是 "     1.    怪物的名稱    ", 數字1 會動態變換。
		std::string msg = "  " + std::to_string(idx + 1) + ". " + monsterCaught->getName();
		this->monsterView->print(3+(idx*2), msg);
	}
	

}

int Player::getMonsterListSize()
{
	return this->monsterList.size();
}


