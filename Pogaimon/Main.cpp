#include "rlutil.h"
#include "Myutil.h"
#include "GameMap.h"
#include "Player.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>



#define waitkey rlutil::anykey("Press any key to continue...\n")
constexpr auto arrow_Left = 75;
constexpr auto arrow_Up = 72;
constexpr auto arrow_Down = 80;
constexpr auto arrow_Right = 77;

char chargen() {
	return rand() % (('~' - '!') + 1) + '!'; // I am really sorry for this
}

int main() {
	{
		// �� resetColor() �����Y�C
		// �I�s resetColor()�A�i�H �^�� saveDefaultColor() ��ɩҰO�����C��C
		//rlutil::saveDefaultColor();
	}

    //myutil::correctionConsole();
	// ���oMAP����A�Ψ�����I���ƥ�AloadMap �|�� map �L�b console�C
    GameMapPtr map = myutil::loadMap("../Pogaimon/assets/yzumap.txt");

	// ���I hardcode
	int x = 20; int y = 30;

	// �إߪ��a
	Player *tony = new Player("tony", x, y);
	/*rlutil::locate(x, y);
	cout << tony->getNotation() << endl;*/
	while (1) {

		// ���ô��
		rlutil::hidecursor();
		// ��m���a
		map->movePlayer( tony, x, y);
		// ������m
		x = tony->getPlayerPosition().x;
		y = tony->getPlayerPosition().y;
		
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
					x = tony->getPlayerPosition().x;
					y = tony->getPlayerPosition().y;
					// shoe log
					rlutil::locate(1, 35);
					cout << "���a��m : x: " << tony->getPlayerPosition().x
						<< ", y: " << tony->getPlayerPosition().y
						<< ", ����cube = \"" << map->returnCubeBy(x, y) << "\"" << endl;
				}
				std::cout.flush();
			}// break;
		}
		
		
	}


	// �^��̷s���
	//rlutil::locate(1, 32);
	return 0;
}
