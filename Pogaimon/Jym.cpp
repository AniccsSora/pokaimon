#include "Jym.h"

Jym::Jym(PlayerPtr P1, PlayerPtr P2)
{
	// P1(���a�p�G�S����b�����~�N�i�h�D�] �s�L�h�Y��)
	if (P1->getMonsterListSize() <= 0) {
		rlutil::cls();
		rlutil::anykey("\n\n     You don't seem to have any Monster. Are you going to fight boxing?     ");
		return;
	}

	// ��l��
	this->P1 = P1;
	this->P2 = P2;
	// ��l�� P1_ascii_veiwList
	for (size_t i = 0; i < P1->getMonsterListSize(); ++i) {
		int mos_idx = P1->getMonIDX_by_MonsList(i);// �q���a���� �ҫ����� monsterList ���h��ڭn�ĴX(i)�ӡA�Ǫ�����Ų�s���C 
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		this->P1_ascii_veiwList.push_back(mos);
	}
	// ��l�� P2_ascii_veiwList
	for (size_t i = 0; i < P2->getMonsterListSize(); ++i) {
		int mos_idx = P2->getMonIDX_by_MonsList(i);// �q���a���� �ҫ����� monsterList ���h��ڭn�ĴX(i)�ӡA�Ǫ�����Ų�s���C 
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		this->P2_ascii_veiwList.push_back(mos);
	}
	
	// ===================== < ��Եe�� View �ѼƳ]�w��>
	// �o�ǰѼƬO�̷� PDF �}���W��h�������C
	int limit_of_Y = 30; //�M�w �h�ְ��� "�}�l"�L�X �ݩ� View�A�]�� ASCII ���קڭ̵L�k�x���C
	int half_x = 50; // �M�w console ������}�l�n���@�b�C
	// ===================== </��Եe�� View �ѼƳ]�w��>
	//for (size_t i = 0; i < P1->getMonsterListSize(); ++i) {
	//	this->P1_mons_asciiManager.clearALLview();// ���M���b�Aascii displayer�C
	//	MySpace::ViewPtr v_ptr = this->P1_ascii_veiwList.at(i);// ���o�Ӫ��a�� ascii
	//	v_ptr->setLeftTop(1,1);//�S�]�w ���W���� �O���o�Q���U�i�h���C
	//	this->P1_mons_asciiManager.registerView(v_ptr);// ���U
	//	rlutil::cls(); // �M�e��
	//	this->P1_mons_asciiManager.showRegisteredView(); // �L�XASCII
	//	rlutil::anykey("\n press any to next");
	//	rlutil::cls();
	//}
	
	// �d���ϥ� ASCII �L�k �T�w���� 
	;
	// ===================== 
	// ��e�d���ݩ�
	
	// ===================== 
	// �� �����d���M�� (�O�_�n�ӤH��?)

	// ===================== 
	// ��԰T��

	// ===================== 
}

void Jym::battle_start()
{
}
