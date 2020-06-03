#pragma once
#include <string>
#include "Monster.h"
#include "MonsterProperty.h"
#include "Mydefine.h"
#include "Displayer.h"
#include "Myutil.h"
#include "rlutil.h"


// Event �����O
class Event
{
public :
	// Do nothing
	Event(){};

	// Ĳ�o���ƥ�A�Ѥl���O�갵
	virtual void touchOff() = 0; //  = 0, �ŧi�� pure virtual function

protected:
	
};

// �D�J Monster �ƥ�
class EncounterMonsterEvent : public Event {

public:
	// �غc�l
	EncounterMonsterEvent(MonsterPropertyList mstPropertyList, Player* servicedPlayer);

	// ��@ �����O�� pure virtual function...(�����[�W virtual ����r)
	virtual void touchOff();

private:
	// �T�{�O�_�n���
	void showStartBattleDialog();
	Monster* encounterMonster =NULL; // EncounterMonsterEvent �غc�l�|�����ƭ�
	Displayer* eventViewList = NULL; // �C���e��~~
	Player* servicedPlayer = NULL;
	MySpace::ViewPtr log_content_view = NULL;
};

// �S���ƥ�A�p�G���a���b �D�S�����ɷ|�^�Ǧ�����C
class NoneEvent : public Event {

	//�غc�l���μg~ �ιw�]���C

	// �L��@�A�����g��@�o���O�|�Q�{���O abstract class.
	// ��@ �����O�� pure virtual function...(�����[�W virtual ����r)
	virtual void touchOff() {
		; // nothing
	}
};

