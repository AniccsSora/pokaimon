#include "Player.h"
#include "Mydefine.h"
#include "GameMap.h"
#include "Myutil.h"


Player::Player(std::string name, int x, int y)
{
	playerName = name;
	position.x = x;
	position.y = y;

	// 初始化一下此玩家 的 holdmonster View。
	MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 40);
	monsterHold_Window->setframeColor(rlutil::YELLOW); // 邊框顏色
	// monsterHold_Window->setLeftTop(100, 6); // 決定 這個View 的位置
	monsterHold_Window->print(1, "  === Player Monster === ");
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
		// TODO : 要讓玩家可以選擇要汰換哪一隻 Monster.
		cout << " Over than three monster\n";
		throw OverThreeMonsterUNHANDLE("TODO : 要讓玩家可以選擇要汰換哪一隻 Monster.");
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


