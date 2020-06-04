#pragma once
#include "Player.h"
#include "Displayer.h"
#include "Mydefine.h"
#include "Myutil.h"

// ��쪱�a�n��ԴN�ӳo��A�� (Player)X 2  �Ƕi�ӡA�̭��|�ݭn�ܦh���F�F
class Jym{
public:
	// �غc�l
	Jym(PlayerPtr P1, PlayerPtr P2);
	// �����}��
	void battle_start();

private:
	PlayerPtr P1 = NULL;
	PlayerPtr P2 = NULL;

	// �޲zP1 �d��(ASCII)�B�d���ݩʡB�����d���M�� �� Displayer ����C
	Displayer P1_ViewManager;
	Displayer P2_ViewManager;
	Displayer battle_log;
};

