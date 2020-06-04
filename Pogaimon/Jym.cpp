#include "Jym.h"

Jym::Jym(PlayerPtr P1, PlayerPtr P2)
{
	// P1(玩家如果沒有抓半隻怪獸就進去道館 叫他去吃屎)
	if (P1->getMonsterListSize() <= 0) {
		rlutil::cls();
		rlutil::anykey("\n\n     You don't seem to have any Monster. Are you going to fight boxing?     ");
		return;
	}

	// 初始化
	this->P1 = P1;
	this->P2 = P2;
	// 初始化 P1_ascii_veiwList
	for (size_t i = 0; i < P1->getMonsterListSize(); ++i) {
		int mos_idx = P1->getMonIDX_by_MonsList(i);// 從玩家物件 所持有的 monsterList 中去選我要第幾(i)個，怪物的圖鑑編號。 
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		this->P1_ascii_veiwList.push_back(mos);
	}
	// 初始化 P2_ascii_veiwList
	for (size_t i = 0; i < P2->getMonsterListSize(); ++i) {
		int mos_idx = P2->getMonIDX_by_MonsList(i);// 從玩家物件 所持有的 monsterList 中去選我要第幾(i)個，怪物的圖鑑編號。 
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		this->P2_ascii_veiwList.push_back(mos);
	}
	
	// ===================== < 對戰畫面 View 參數設定區>
	// 這些參數是依照 PDF 開的規格去評估的。
	int limit_of_Y = 30; //決定 多少高度 "開始"印出 屬性 View，因為 ASCII 高度我們無法掌握。
	int half_x = 50; // 決定 console 的哪邊開始要分一半。
	// ===================== </對戰畫面 View 參數設定區>
	//for (size_t i = 0; i < P1->getMonsterListSize(); ++i) {
	//	this->P1_mons_asciiManager.clearALLview();// 先清乾淨，ascii displayer。
	//	MySpace::ViewPtr v_ptr = this->P1_ascii_veiwList.at(i);// 取得該玩家的 ascii
	//	v_ptr->setLeftTop(1,1);//沒設定 左上角的 是不得被註冊進去的。
	//	this->P1_mons_asciiManager.registerView(v_ptr);// 註冊
	//	rlutil::cls(); // 清畫面
	//	this->P1_mons_asciiManager.showRegisteredView(); // 印出ASCII
	//	rlutil::anykey("\n press any to next");
	//	rlutil::cls();
	//}
	
	// 寵物圖示 ASCII 無法 確定高度 
	;
	// ===================== 
	// 當前寵物屬性
	
	// ===================== 
	// 當 持有寵物清單 (是否要個人化?)

	// ===================== 
	// 對戰訊息

	// ===================== 
}

void Jym::battle_start()
{
}
