#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:
	// 顯示 某個 View
	void showView();
	// 增加某個 View 到 viewList 內。
	void addView(MySpace::View view);
private:
	// 將訊息印在 畫面，這是透過  showGameMap()內呼叫的。
	void showGameMapLog();
	std::vector<MySpace::View> viewList;
};

