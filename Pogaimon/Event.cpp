#include "Event.h"



// �غc�l
EncounterMonsterEvent::EncounterMonsterEvent(MonsterPropertyList mstPropertyList,Player* servicedPlayer):Event(){
	// �H�K�ͤ@�өǪ�~~
	this->encounterMonster = new Monster(rand(), mstPropertyList);
	
	// �� display ����
	this->eventViewList = new Displayer();

	// �ҪA�Ȫ����a
	this->servicedPlayer = servicedPlayer;

	// log ���e�� View�C
	//log_content_view = �̫᭱�A�[�J;

	// ���@�� View
	//=============================================================================

	//  �d���ݩʪ� View
	MySpace::ViewPtr monsterProperty = myutil::createView('*', 15, 40);
	monsterProperty->setLeftTop(80, 2);
	
	monsterProperty->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
	monsterProperty->print(4, " ************************************ ");
	monsterProperty->print(5, "  Index - : " + std::to_string(this->encounterMonster->getIdx()));
	monsterProperty->print(6, "  Name -- : " + this->encounterMonster->getName());
	monsterProperty->print(7, "  Type -- : " + this->encounterMonster->getTypeStr());
	monsterProperty->print(8, "  HP ---- : " + std::to_string(this->encounterMonster->getHp()));
	monsterProperty->print(9, "  ATK --- : " + std::to_string(this->encounterMonster->getAtk()));
	monsterProperty->print(10, "  DEF --- : " + std::to_string(this->encounterMonster->getDef()));
	monsterProperty->print(11, "  SPEED - : " + std::to_string(this->encounterMonster->getSpeed()));
	monsterProperty->print(12, "  Ability : " + this->encounterMonster->getAbilityNameByAbliIdx( this->encounterMonster->getAbilityIdx()));
	this->eventViewList->registerView(monsterProperty);// �d���ݩ� �� View
	//=============================================================================

	//  ASCII ��  (�d���b console ���ϥ�)�C
	MySpace::ViewPtr ascii = myutil::getMonsterASCIIViewPtrbyIdx(this->encounterMonster->getIdx());
	ascii->setLeftTop(1, 1);
	this->eventViewList->registerView(ascii);//  ASCII�� �� View
	//=============================================================================
	short logger_w = 40, MostleftTop_Y = 31;// for log view
	short MostleftTop_X = 80;// for log view, Player.cpp::addMonster() �|�ϥΦ��ƭ�(���O�ܼ�)�C
	short title_H = 3, content_H = 7;// for log view
	short holdMonsterView_Y = 20;// for monater, Player.cpp::addMonster() �|�ϥΦ��ƭ�(���O�ܼ�)�C
	//=============================================================================
	// ���a���� monster View
	// map �W�� view ��m��o�Ӥ��@�ˡA���ڤ��Q�n�ޤӦh���ܽƻs�@�Өӧ��m�N�i�H�ܵΪA�F
	MySpace::View* src = servicedPlayer->getHoldMonsterView();
	MySpace::View* copied_Player_Hole_Monster_View = new MySpace::View(*src);
	// ���a���� monster View
	copied_Player_Hole_Monster_View->setLeftTop(MostleftTop_X, holdMonsterView_Y); // 
	copied_Player_Hole_Monster_View->setframeColor(rlutil::LIGHTBLUE);
	this->eventViewList->registerView(copied_Player_Hole_Monster_View);// �����Ǫ��� View�C
	//=============================================================================
	// ���ܰT�� View Title
	MySpace::ViewPtr loggerTitle = myutil::createView('L', title_H, logger_w); // ���D�ϰ� ��o��� View ���_��(��ı�W�����@��View)�C
	loggerTitle->setLeftTop(MostleftTop_X, MostleftTop_Y);
	int speceSize = 13;
	loggerTitle->print(2, std::string(speceSize, ' ')+"~~ Message ~~"+std::string(speceSize,' '));
	loggerTitle->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(loggerTitle);//log View Title

	// ���ܰT�� View Content
	MySpace::ViewPtr logger = myutil::createView('L', content_H, logger_w);
	logger->setLeftTop(MostleftTop_X, MostleftTop_Y + content_H- title_H);
	logger->print(2, "  Press \"SPACE\" to return to the map. ");
	logger->print(4, "  Press \" C \" try catch monster.");
	logger->print(6, "  >");
	logger->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(logger);// log View Content
	// ��s Event �n�Ϊ��C
	this->log_content_view = logger;
	//=============================================================================

	// �Х� View <End>
	
}

// �D�J�� monster ����@
void EncounterMonsterEvent::touchOff(){
	// �J�� �ǩԣ���������
	// this->encounterMonster;
	
	
	rlutil::cls();

	this->eventViewList->showRegisteredView();
	
	//this->monster
	rlutil::locate(84, 41);
	rlutil::showcursor();

	while (true) {
		if (kbhit()) {
			// ������L
			char k = getch(); // Get character
			if (k == 'C' || k == 'c') { 
				rlutil::hidecursor();
				if (this->servicedPlayer->getMonsterListSize() < 3) {
					cout << "  Start Catch-> " + this->encounterMonster->getName();
					rlutil::msleep(500);
				}
				else { // Hardcode �ק� Message View ���T���C �N�O�o������XD�C
					int view_x_ptr, view_y_ptr;
					view_x_ptr = this->log_content_view->status.lefttop.x+1; 
					view_y_ptr = this->log_content_view->status.lefttop.y + 2;//
					rlutil::locate(view_x_ptr, view_y_ptr);//locate�� �Ĥ@�� �}�Y��m
					cout << std::string(40, ' ');//�M�ŸӰ�
					rlutil::locate(view_x_ptr, view_y_ptr);//�A���^�� �Ĥ@�� �}�Y��m�A���ɬO�ťժ��C
					cout << std::string("  Press \"ESC\" to abort the crawl.");
					// ���U�ӥh��ĤG�� msg "Press " C " try catch..."
					// logger->print(4, "  Press \" C \" try catch monster.");
					rlutil::locate(view_x_ptr, view_y_ptr+2);//�� �ĤG�� �}�Y��m
					cout << std::string(40, ' '); //�M�ŸӰ�
					rlutil::locate(view_x_ptr, view_y_ptr + 2);//�^�� �ĤG�� �}�Y��m
					cout << std::string("  Press \" R \" to replace the monster.");

					rlutil::saveDefaultColor();
					rlutil::setColor(rlutil::LIGHTRED);
					rlutil::locate(view_x_ptr+4, view_y_ptr + 4);//�� �ĤT�� �}�Y��m
					cout << "Use the \'W\',\'S\' buttons to replace.";
					rlutil::resetColor();
				}
				this->servicedPlayer->addMonster(this->encounterMonster); // �|�@ �j�� 3���ˬd
				
				break;
			}
			else if (k == ' ') { 
				this->log_content_view->print(6, "  Cancel catch...");
				rlutil::locate(84, 41); //harcode.
				cout << "  Cancel catch...";
				//this->eventViewList->showRegisteredView();// ��Ӧr ��ϭ��L...// ���ӹL�h�į�
				rlutil::hidecursor();
				rlutil::msleep(500);
				break; 
			}
		}
		std::cout.flush();
	}
	rlutil::cls();
}

EncounterNPCEvent::EncounterNPCEvent(Player* player, PlayerPtr encounterNpc)
{
	// ��l��
	this->player = player;
	this->encounterNpc = encounterNpc;
}

void EncounterNPCEvent::touchOff(){
	Jym *myJJ = new Jym(player, encounterNpc); // TODO: �n�O�o�R���C
	myJJ->battle_start();
}
