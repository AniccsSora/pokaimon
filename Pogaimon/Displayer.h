#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:

	// 啥事都不會做~~~
	Displayer();

	// 顯示 某個 View, 在 console 上。
	void showView(MySpace::ViewPtr view, short x, short y);
	
	// 印出 有帶 座標 的 View。
	void showView(MySpace::ViewPtr view);
	
	// 印出 所有已註冊的 View
	void showRegisteredView();

	// 添加 View 到 viewList裡面。
	// ** 沒有 給定 lefttop 的 View **, 是不得被註冊進去的。
	void registerView(MySpace::ViewPtr view);

	// 清除所有已經被註冊的 View
	void clearALLview();

private:
	MySpace::Vec_1D_<MySpace::ViewPtr> viewList;
};

