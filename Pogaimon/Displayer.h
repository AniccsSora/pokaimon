#pragma once
#include <vector>
#include "Mydefine.h"

class Displayer
{
public:

	// ԣ�Ƴ����|��~~~
	Displayer();

	// ��� �Y�� View, �b console �W�C
	void showView(MySpace::View view, short x, short y);
	
	// �L�X ���a �y�� �� View�C
	void showView(MySpace::View view);
	
	// �L�X �Ҧ��w���U�� View
	void showRegisteredView();

	// �K�[ View �� viewList�̭��C
	// ** �S�� ���w lefttop �� View **, �O���o�Q���U�i�h���C
	void registerView(MySpace::View &view);

private:
	MySpace::Vec_1D_<MySpace::View> viewList;
};

