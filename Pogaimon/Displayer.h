#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:

	// 啥事都不會做~~~
	Displayer();

	// 顯示 某個 View, 在 console 上。
	void showView(MySpace::View view, short x, short y);
	
	// 印出 有帶 座標 的 View。
	void showView(MySpace::View view);
	
	// 印出 所有已註冊的 View
	void showRegisteredView();

	// 添加 View 到 viewList裡面。
	// ** 沒有 給定 lefttop 的 View **, 是不得被註冊進去的。
	void registerView(MySpace::View &view);

private:
	MySpace::Vec_1D_<MySpace::View> viewList;
};

