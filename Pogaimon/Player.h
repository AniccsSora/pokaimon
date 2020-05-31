#pragma once
#include <string>
#include "Mydefine.h"


class Player
{
public:
	// ���a�غc�l�A���ѦW�r �H�Ψ�ͦ��I�y�СC
	Player(std::string name,int x,int y);

	// �^�Ǫ��a�{�b�b���y�СA��GameMap�S���b�����Y�A�o�u�O�@�� "�y��"�C
	struct MySpace::Coordi getPlayerPosition();

	// �^�ǥN�����a���Ÿ�, Default = '@'
	char getNotation();

	// �]�w���a�y�СA�S�����b�L�N�O�]�w������"�y��"�ѼơC
	void setPosition(MySpace::Coordi newPosition);

	// �^�Ǫ��a name.
	std::string getName();

	// �b console show �X ���a
	void showMe_by_coord();

	// �]�w���a�C��
	void setColor(rlutil_Color c);

	// ���o���a�C��
	rlutil_Color getColor();

	//

private:
	// ���a�b�a�Ϫ���m, 1-base�C
	struct MySpace::Coordi position;

	// ���a�W��
	std::string playerName;

	// ���a�Ÿ�
	char notation = '@';

	// ���a�C��
	int color = rlutil::WHITE;
};

