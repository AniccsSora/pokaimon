#include "Player.h"
#include "Mydefine.h"
#include "GameMap.h"
#include "Myutil.h"


Player::Player(std::string name, int x, int y)
{
	playerName = name;
	position.x = x;
	position.y = y;

	// ��l�Ƥ@�U�����a �� holdmonster View�C
	MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 40);
	monsterHold_Window->setframeColor(rlutil::YELLOW); // ����C��
	// monsterHold_Window->setLeftTop(100, 6); // �M�w �o��View ����m
	monsterHold_Window->print(1, "  === Player Monster === ");
	monsterHold_Window->print(3, "  1. None");
	monsterHold_Window->print(5, "  2. None");
	monsterHold_Window->print(7, "  3. None");
	// �ᤩ player���� ��l�ƪ� View�C
	this->monsterView = monsterHold_Window;
}

MySpace::Coordi Player::getPlayerPosition()
{
	return position;
}

char Player::getNotation()
{
	return notation;
}

void Player::setPosition(MySpace::Coordi newPosition)
{
	position = newPosition;
}

std::string Player::getName()
{
	return playerName;
}


void Player::showMe_by_coord()
{
	rlutil::setColor(getColor());
	rlutil::locate(position.x, position.y);
	std::cout << notation;
}

void Player::setColor(rlutil_Color c)
{
	color = c;
}

rlutil_Color Player::getColor()
{
	return color;
}

MySpace::ViewPtr Player::getHoldMonsterView()
{
	// �غc�ɴN���F �S���n�A�����ءC
	//// �p�G�ڥ��S�� View �Q������o�� ���a���󨭤W�C
	//if (this->monsterView == NULL) { // �����a�s�W View
	//	MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 30);
	//	monsterHold_Window->setframeColor(rlutil::YELLOW); // ����C��
	//	// monsterHold_Window->setLeftTop(100, 6); // �Ȥ��M�w
	//	monsterHold_Window->print(1, "  === Player Monster === ");
	//	monsterHold_Window->print(3, "  1. None");
	//	monsterHold_Window->print(5, "  2. None");
	//	monsterHold_Window->print(7, "  3. None");

	//	this->monsterView = monsterHold_Window;
	//}

	return this->monsterView;
}

void Player::setMonsterView_FT(int x, int y)
{ 
	this->monsterView->setLeftTop(x, y);
}

// �W�L�T�ӫ���?
void Player::addMonster(MonsterPtr monsterCaught) throw(OverThreeMonsterUNHANDLE)
{
	// monsterList�BmonsterView

	if (this->monsterList.size() >= 3) {
		// TODO : �n�����a�i�H��ܭn�O�����@�� Monster.
		cout << " Over than three monster\n";
		throw OverThreeMonsterUNHANDLE("TODO : �n�����a�i�H��ܭn�O�����@�� Monster.");
	}
	else { // ���ǥ[�J �� monster list
		// Add monster to list.
		this->monsterList.push_back(monsterCaught);

		// ���o�{�b monsterList �̤j idx�C
		int idx = this->monsterList.size()-1;

		// Add View
		// �ھ� hardcode : ���~�i�L�欰 3, 5, 7�C

		// �榡�j���O "     1.    �Ǫ����W��    ", �Ʀr1 �|�ʺA�ܴ��C
		std::string msg = "  " + std::to_string(idx + 1) + ". " + monsterCaught->getName();
		this->monsterView->print(3+(idx*2), msg);
	}
	

}


