#include "Event.h"



// �غc�l
EncounterMonsterEvent::EncounterMonsterEvent(MonsterPropertyList mstPropertyList,Player* servicedPlayer):Event(){
	// �H�K�ͤ@�өǪ�~~
	this->monster = new Monster(rand(), mstPropertyList);
	// �� display ����
	this->eventViewList = new Displayer();

	// ���@�� View

	// �k�W�� View
	MySpace::ViewPtr monsterProperty = myutil::createView('*', 3, 20);
	monsterProperty->setLeftTop(100, 2);
	monsterProperty->print(2, "  Type: " + this->monster->getTypeStr());

	// ���W�� ASCII �ϡA  (�d���b console ���ϥ�)�C
	MySpace::ViewPtr ascii = myutil::getMonsterASCIIViewPtrbyIdx(this->monster->getIdx());
	ascii->setLeftTop(1, 1);
	this->eventViewList->registerView(ascii);// ���W�� View

	// ���a���� monster�C�� View<Start>
	short logger_w = 40, MostleftTop_X = 80, MostleftTop_Y = 20;
	short title_H = 3, content_H = 7;

	// ���ܰT�� View Title
	MySpace::ViewPtr loggerTitle = myutil::createView('L', title_H, logger_w); // ���D�ϰ� ��o��� View ���_��(��ı�W�����@��View)�C
	loggerTitle->setLeftTop(MostleftTop_X, MostleftTop_Y);
	int speceSize = 13;
	loggerTitle->print(2, std::string(speceSize, ' ')+"~~ ���ܰT�� ~~"+std::string(speceSize,' '));
	loggerTitle->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(loggerTitle);// ���W�� View Title

	// ���ܰT�� View Content
	MySpace::ViewPtr logger = myutil::createView('L', content_H, logger_w);
	logger->setLeftTop(MostleftTop_X, MostleftTop_Y + content_H- title_H);
	logger->print(2, "  ���U �ť��� �^��a��... ");
	logger->print(4, "  ���U \" C \" �}�l����...");
	logger->print(6, "  ��L�T��~~~~~          ");
	logger->setframeColor(rlutil::YELLOW);
	this->eventViewList->registerView(logger);// ���W�� View
	// ���a���� monster�C�� View <End>

	this->eventViewList->registerView(monsterProperty);// �k�W�� View
}

// �D�J�� monster ����@
void EncounterMonsterEvent::touchOff(){
	// �J�� �ǩԣ���������
	rlutil::cls();

	this->eventViewList->showRegisteredView();
	//this->monster

	while (true) {
		if (kbhit()) {
			// ������L
			char k = getch(); // Get character
			if (k == 'C' || k == 'c') { 
				std::cout << "�}�l����...\n";
				rlutil::anykey();
				break;
			}
			else if (k == ' ') { break; }
		}
		std::cout.flush();
	}
	rlutil::cls();
}
