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

	// �d��(ASCII) = �ϥܹ��� monsterList ����
	MySpace::Vec_1D_<MySpace::ViewPtr> P1_ascii_veiwList;
	MySpace::Vec_1D_<MySpace::ViewPtr> P2_ascii_veiwList;

	// �޲z�B�d���ݩʡB�����d���M�� �� Displayer ����C
	Displayer P1_ViewManager;
	Displayer P1_mons_asciiManager; // �u��@��View�A�]�u�βĤ@��View�A�n�ϥήɤ~�| �I�s, ���Ϊ�l��
	Displayer P2_ViewManager;
	Displayer P2_mons_asciiManager; // �u��@��View�A�]�u�βĤ@��View�A�n�ϥήɤ~�| �I�s, ���Ϊ�l��
	Displayer battle_log;
};


