#include "Player.h"
#include "Mydefine.h"
#include "GameMap.h"
#include "Myutil.h"
#include <cctype>
#include <iostream>

Player::Player(std::string name, int x, int y)
{
	playerName = name;
	position.x = x;
	position.y = y;

	// ��l�Ƥ@�U�����a �� holdmonster View�C
	MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 40);
	monsterHold_Window->setframeColor(rlutil::YELLOW); // ����C��
	// monsterHold_Window->setLeftTop(100, 6); // �M�w �o��View ����m
	monsterHold_Window->print(1, "  === Player's Monster === ");
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
		int last_x = -1, last_y;
		int x = -1, y = -1; // console ��Щw��ΡC
		// TODO : �n�����a�i�H��ܭn�O�����@�� Monster.
		/*cout << " Over than three monster\n";
		throw OverThreeMonsterUNHANDLE("TODO : �n�����a�i�H��ܭn�O�����@�� Monster.");*/

		// ��� ���� player monster View �� �Ĥ@��(1-base:4) ���̧��� (�򥻤W monsterList �� monsterView ���ƭȭn�@��)
		int locate_View_X_idx = -1; // �H�� View��LF����ǡA�ڭ̭nlocate �� X ��m�C
		char previous_char = ' ';// �����W�@�� char
		
		// ���ӬO monster View �Y element(�C) �����
		MySpace::Vec_1D_<char> target_row = this->monsterView->element[3];
		if (target_row.size() > 0) {
			int row_size = target_row.size();
			for (size_t idx = 1; idx < row_size; ++idx) { // ���X �� row �����A�w��̫�@�Ӧr.(idx=1�O�]�������)
				const char this_char = target_row.at(idx);// �����ثe���쪺 idx.
				if (isalpha(previous_char) && isspace(this_char)) {// ��e�@�ӬO�r�� �B ����m�O�ť�
					locate_View_X_idx = idx;
					break;
				}
				previous_char = this_char;
			}
			// �w�� �]���j��(locate_View_X_idx)�٬O�z���C
			if (locate_View_X_idx < 0) { throw OverThreeMonsterUNHANDLE(" Err: locate_View_X_idx still < 0.");  }
			else { // �w�즨�\
				//�n�� View �� �۹�y�СA�Ǵ�������(console �� x,y)
				int MostleftTop_X = 80, holdMonsterView_Y = 23; // Console�y�СAhardcode from "Event.cpp"
				x = MostleftTop_X + locate_View_X_idx;
				y = holdMonsterView_Y;
				rlutil::locate(x, y); // ��и��D����
				//rlutil::showcursor();
			}

		}else { throw OverThreeMonsterUNHANDLE(" Err: �Ĥ@�檺 monster �T��size() < 0"); }

		std::vector<int> canLocate_Y = { y , y + 2 , y + 4 }; // ���Х�
		int canLocate_Y_idx = 0;
		x += 5;// �첾�@�U�y�СC (�ܥi���z��)
		// ��ť��L �W�U �n�i�H���� 1~3 �ϰ� ��L Esc (X)��^�A�ť� �����C(3,5,7)1-base
		std::string lock_msg = " <- Replace this."; //��� ����T
		rlutil::locate(x, canLocate_Y[canLocate_Y_idx]);
		rlutil::saveDefaultColor();
		rlutil::setColor(rlutil::GREEN);
		std::cout << lock_msg; //  �L�X "���"
		rlutil::resetColor();
		while (true) {
			rlutil::hidecursor();
			if (kbhit()) {
				// ������L
				last_y = canLocate_Y[canLocate_Y_idx]; // �����W�� y
				char k = getch(); // Get character
				if (k == 'w'||k=='W') { 
					--canLocate_Y_idx; 
					canLocate_Y_idx += 3;
					canLocate_Y_idx %= 3; 
				}
				else if (k == 's'|| k=='S') {  
					++canLocate_Y_idx; 
					canLocate_Y_idx += 3;
					canLocate_Y_idx %= 3;
				}
				else if ( 'r' == k || 'R' == k) {
					// ���� monster List ������
					this->monsterList.at(canLocate_Y_idx);
					// ��s�F��� View �]�n��s
					// 0 1 2  -> 3 5 7 (idx ���� View ����ڦC��)
					// ��s View �� ���e
					std::string ms_name = "  " + std::to_string(canLocate_Y_idx + 1) + ". " + monsterCaught->getName();
					this->monsterView->print(3 + (canLocate_Y_idx * 2), ms_name);
					break;
				}
				else if ( 27 == k) { // ESC
					break; 
				}
				rlutil::locate(x, last_y);// ���ܮy��
				
				std::cout << std::string(lock_msg.size(),' '); //  �M�� "���" 
				rlutil::locate(x, canLocate_Y[canLocate_Y_idx]);// ���ܮy��
				rlutil::saveDefaultColor();
				rlutil::setColor(rlutil::GREEN);
				std::cout << lock_msg; //  �L�X "���"
				rlutil::resetColor();
			}
			std::cout.flush();
		}


		// ����w�� Monster �� delete ������� �� �ثe�n�쪺 monster�C
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

int Player::getMonsterListSize()
{
	return this->monsterList.size();
}


