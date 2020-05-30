#include "rlutil.h"
#include "Myutil.h"
#include "GameMap.h"
#include "Player.h"
#include "Displayer.h"
#include "InfoProvider.h"
#include "Monster.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>



#define waitkey rlutil::anykey("Press any key to continue...\n")
constexpr auto arrow_Left = 75;
constexpr auto arrow_Up = 72;
constexpr auto arrow_Down = 80;
constexpr auto arrow_Right = 77;

char chargen() {
	return rand() % (('~' - '!') + 1) + '!'; // I am really sorry for this
}

int main() {
	srand(time(NULL));
	//================ test~~
	while (0) {
		// ���o�d���Ѽƹ�Ų
		//MonsterPropertyList mstPropertyList = myutil::loadMonsterFile();
		//// ���o�۫g��
		//TypeTable typeTable = myutil::getDamageRatioTable();

		//int idx = 1;
		//MonsterPtr DAJJ = new Monster(rand(), mstPropertyList);
		//MonsterPtr DAGG = new Monster(rand(), mstPropertyList);

		//cout << typeTable.at(DAJJ->getType()).at(DAGG->getType()) << endl;
		//MySpace::ViewPtr ascii =  myutil::getMonsterASCII(5);

		rlutil::anykey("test end...");
	}
	//================
	rlutil::saveDefaultColor();
	//myutil::screen_ruler(); waitkey;

	// ��l�� �@�Ǫ���A�a�ϡB���a�B�C�����U���O(���h��)...
	//===============
	// ���oMAP����A�Ψ�����I���ƥ�AloadMap �|�Ǧ^ *map�C
	GameMapPtr map = myutil::loadMap("../Pogaimon/assets/yzumap.txt");

	// ���a���߭��I, hardcode
	int x = 20; int y = 30;

	// �إߪ��a, ���W�r ���ͦ��y�СC
	Player* tony = new Player("tony", x, y);

	// ���� console �� View ����ܡC
	Displayer viewManager;

	// �]�w�@��View... 
	MySpace::ViewPtr ascii = myutil::getMonsterASCII(5); //�p���s
	ascii->setLeftTop(100, 50);
	viewManager.registerView(ascii);

	// log �ϰ�C
	MySpace::ViewPtr log_Window = myutil::createView('*', 5, 60); // �M�w View ���j�p
	log_Window->setLeftTop(65, 23); // �M�w �o��View ����m
	log_Window->setframeColor(rlutil::GREEN);
	viewManager.registerView(log_Window);// �N�Q�n�Q��ܪ� View ���U�i Displayer �޲z�C

	// ��ܪ��a�����d���Ϊ� View
	MySpace::ViewPtr monsterHold_Window = myutil::createView('O', 8, 30);
	monsterHold_Window->setframeColor(rlutil::YELLOW); // ����C��
	monsterHold_Window->setLeftTop(100, 6); // �M�w �o��View ����m
	viewManager.registerView(monsterHold_Window);// �N�Q�n�Q��ܪ� View ���U�i Displayer �޲z�C
	monsterHold_Window->print(1, "  === ���a���� Monster === ");
	monsterHold_Window->print(3, "  1. �L");
	monsterHold_Window->print(5, "  2. �L");
	monsterHold_Window->print(7, "  3. �L");


	// ���a info �������O, �|�t�d�^�Ǥ@�� log(std::string).
	InfoProvider tonyInfoService(tony, map);
	//=============== ��l�Ƨ���
	
	while (1) {
		
		// ���ô��
		rlutil::hidecursor();

		// ��m���a
		// map->movePlayer( tony, x, y);

		// ������m
		x = tony->getPlayerPosition().x;
		y = tony->getPlayerPosition().y;

		// �L�X �a�ϡA�|���a�C���ܤ�
		map->showMap_and_Player(*tony);

		// ����w�� View ���w �T���C
		log_Window->print(1, tonyInfoService.getPlayerPositionMsg());
		log_Window->print(3, " ���O�D�J = ");

		// �L�X Displayer �Һ޲z�� view����C
		viewManager.showRegisteredView();

		// Player move ���� �H�ΦU�B�o�ƥ�
		{
			while (true) {
				if (kbhit()) {
					// ������L
					char k = getch(); // Get character
					if (k == arrow_Left) { --x; }
					else if (k == arrow_Right) { ++x; }
					else if (k == arrow_Up) { --y; }
					else if (k == arrow_Down) { ++y; }
					else if (k == ' ') { break; }
					// ��m���a
					map->movePlayer(tony, x, y);
					// ������m
					x = tony->getPlayerPosition().x; y = tony->getPlayerPosition().y;
					 
					// show log
					// ����w�� View ���w �T���C
					log_Window->print(1,tonyInfoService.getPlayerPositionMsg()); // 

					// �L�X Displayer �Һ޲z�� view����C
					viewManager.showRegisteredView();
				}
				std::cout.flush();
			}// break ����a;

			// �U���B�z �԰�???
		}
	}
	return 0;
}
