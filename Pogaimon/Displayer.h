#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:

	// ���w ��ܮy�СC
	Displayer();

	// ��� �Y�� View
	void showView();

	// �W�[�Y�� View �� viewList ���C
	void addView(MySpace::View view);

private:
	//
	

	// �O���ۦ� displayer �ұ��ު� View�C
	std::vector<MySpace::View> viewList;
};

