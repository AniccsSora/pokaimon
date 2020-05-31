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

	// ���a���� monster�C�� View

	this->eventViewList->registerView(monsterProperty);// �k�W�� View
}

// �D�J�� monster ����@
void EncounterMonsterEvent::touchOff(){
	// �J�� �ǩԣ���������
	rlutil::cls();

	this->eventViewList->showRegisteredView();
	//this->monster

	rlutil::anykey("���U���N����^��a��...\n");
	rlutil::cls();
}
