#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:

	// ԣ�Ƴ����|��~~~
	Displayer();

	// ��� �Y�� View, �b console �W�C
	void showView(std::string viewName);

	// �W�[�Y�� View �� viewList ���C (view �u�[����~)�C
	void addView(MySpace::View view);

private:

	// �w�g�Q�ϥΪ� �e���Ŷ��A�qdisplayer �إߨ�{�b���ɶ��C
	std::vector<MySpace::ViewStatus> usedSpace;

	// �O���ۦ� displayer �U�ұ��ު� View�C
	std::vector<MySpace::View> viewList;
};

