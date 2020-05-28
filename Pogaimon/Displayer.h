#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:

	// 給定 顯示座標。
	Displayer();

	// 顯示 某個 View
	void showView();

	// 增加某個 View 到 viewList 內。
	void addView(MySpace::View view);

private:
	//
	

	// 記錄著此 displayer 所控管的 View。
	std::vector<MySpace::View> viewList;
};

