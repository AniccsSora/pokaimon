#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:
	// ��� �Y�� View
	void showView();
	// �W�[�Y�� View �� viewList ���C
	void addView(MySpace::View view);
private:
	// �N�T���L�b �e���A�o�O�z�L  showGameMap()���I�s���C
	void showGameMapLog();
	std::vector<MySpace::View> viewList;
};

