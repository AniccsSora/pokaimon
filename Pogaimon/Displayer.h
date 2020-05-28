#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:

	// 啥事都不會做~~~
	Displayer();

	// 顯示 某個 View, 在 console 上。
	void showView(std::string viewName);

	// 增加某個 View 到 viewList 內。 (view 只加不減~)。
	void addView(MySpace::View view);

private:

	// 已經被使用的 畫面空間，從displayer 建立到現在的時間。
	std::vector<MySpace::ViewStatus> usedSpace;

	// 記錄著此 displayer 下所控管的 View。
	std::vector<MySpace::View> viewList;
};

