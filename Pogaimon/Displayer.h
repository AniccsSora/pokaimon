#pragma once
#include <vector>
#include "Mydefine.h"

struct View {
	Vec_2D_<char> element;
};

class Displayer
{
public:
	// 顯示 遊戲地圖
	void showGameMap();
private:
	// 將訊息印在 畫面，這是透過  showGameMap()內呼叫的。
	void showGameMapLog();
	
};

