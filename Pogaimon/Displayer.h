#pragma once
#include <vector>
#include "Mydefine.h"

struct View {
	Vec_2D_<char> element;
};

class Displayer
{
public:
	// ��� �C���a��
	void showGameMap();
private:
	// �N�T���L�b �e���A�o�O�z�L  showGameMap()���I�s���C
	void showGameMapLog();
	
};

