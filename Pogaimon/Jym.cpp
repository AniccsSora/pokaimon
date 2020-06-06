#include "Jym.h"
#include <algorithm>

Jym::Jym(PlayerPtr P1, PlayerPtr P2)
{

	// P1(玩家如果沒有抓半隻怪獸就進去道館 叫他去吃屎)
	if (P1->getMonsterListSize() <= 0) {
		rlutil::cls();
		rlutil::anykey("\n\n     You don't seem to have any Monster. Are you going to fight boxing?     ");
		return;
	}


	// ===================== < 對戰畫面 View 參數設定區>
	// 這些參數是依照 PDF 開的規格去評估的。

	//決定 多少高度 "開始"印出 屬性 View，因為 ASCII 高度有待評估。
	int limit_of_property = 30; 
	// 決定 console 的哪邊開始要分一半。開始印出 P2 的資料
	int half_x = 70;

	// P1,P2 開始印 ascii View 的座標
	int P1_asciiView_X = 1 , P1_asciiView_Y = 1;
	int P2_asciiView_X = 92, P2_asciiView_Y = 1;
	
	// P1, P2 寵物屬性 Property View 座標
	int P1_pp_view_X = 41 , P1_pp_view_Y = 5;
	int P2_pp_view_X = 134, P2_pp_view_Y = 5;

	// P1，P2 開始印 持有寵物 View 的座標
	int P1_ViewHoldMos_X = P1_pp_view_X, P1_ViewHoldMos_Y = 26;
	int P2_ViewHoldMos_X = P2_pp_view_X, P2_ViewHoldMos_Y = 26;

	// Log 開始印的高度
	int log_x = 40, log_y = 37;
	// ===================== </對戰畫面 View 參數設定區>

	// 初始化
	this->P1 = P1;
	this->P2 = P2;

	// 初始化 P1_DisplayerList (裡面存著 ascii View Displayer; 不同的 view 不同的 Displayer)
	for (size_t i = 0; i < P1->getMonsterListSize(); ++i) {
		int mos_idx = P1->getMonIDX_by_MonsList(i);// 從玩家物件 所持有的 monsterList 中去選我要第幾(i)個，怪物的圖鑑編號。 
		Displayer* tmp_dis = new Displayer();
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		mos->setLeftTop(P1_asciiView_X, P1_asciiView_Y);// 註冊View 前要 設定 LT。
		tmp_dis->registerView(mos);
		this->P1_DisplayerList.push_back(*tmp_dis);
	}
	// 初始化 P2_DisplayerList
	for (size_t i = 0; i < P2->getMonsterListSize(); ++i) {
		int mos_idx = P2->getMonIDX_by_MonsList(i);// 從玩家物件 所持有的 monsterList 中去選我要第幾(i)個，怪物的圖鑑編號。 
		Displayer* tmp_dis = new Displayer();
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		mos->setLeftTop(P2_asciiView_X, P2_asciiView_Y);// 註冊View 前要 設定 LT。
		tmp_dis->registerView(mos);
		this->P2_DisplayerList.push_back(*tmp_dis);
	}
	
	// 上方有幫每個 P1 ,Displayer 註冊 ASCII View，這邊要註冊 Monster Propterty View.
	for (size_t i = 0; i < this->P1_DisplayerList.size(); ++i){
		MySpace::ViewPtr property = myutil::createView('*', 13, 40);
		MonsterPtr mos = P1->getMonsterList().at(i);//取得一隻怪獸

		// 資料寫入View
		property->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
		property->print(4, " ************************************ ");
		property->print(5, "  Index - : " + std::to_string(mos->getIdx()));
		property->print(6, "  Name -- : " + mos->getName());
		property->print(7, "  Type -- : " + mos->getTypeStr());
		property->print(8, "  HP ---- : " + std::to_string(mos->getHp()));
		property->print(9, "  ATK --- : " + std::to_string(mos->getAtk()));
		property->print(10, "  DEF --- : " + std::to_string(mos->getDef()));
		property->print(11, "  SPEED - : " + std::to_string(mos->getSpeed()));
		property->print(12, "  Ability : " + mos->getAbilityNameByAbliIdx(mos->getAbilityIdx()));

		property->setLeftTop(P1_pp_view_X, P1_pp_view_Y);// 設定 Property 座標
		this->P1_DisplayerList[i].registerView(property);
	}
	
	// 上方有幫每個 P2 ,Displayer 註冊 ASCII View，這邊要註冊 Monster Propterty View.
	for (size_t i = 0; i < this->P2_DisplayerList.size(); ++i) {
		MySpace::ViewPtr property = myutil::createView('*', 13, 40);
		MonsterPtr mos = P2->getMonsterList().at(i);//取得一隻怪獸

		// 資料寫入View
		property->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
		property->print(4, " ************************************ ");
		property->print(5, "  Index - : " + std::to_string(mos->getIdx()));
		property->print(6, "  Name -- : " + mos->getName());
		property->print(7, "  Type -- : " + mos->getTypeStr());
		property->print(8, "  HP ---- : " + std::to_string(mos->getHp()));
		property->print(9, "  ATK --- : " + std::to_string(mos->getAtk()));
		property->print(10, "  DEF --- : " + std::to_string(mos->getDef()));
		property->print(11, "  SPEED - : " + std::to_string(mos->getSpeed()));
		property->print(12, "  Ability : " + mos->getAbilityNameByAbliIdx(mos->getAbilityIdx()));

		property->setLeftTop(P2_pp_view_X, P2_pp_view_Y);// 設定 Property 座標
		this->P2_DisplayerList[i].registerView(property);
	}
	// ===================== 

	// ===================== 

	// P1，P2 持有寵物清單。
	// 當 持有寵物清單，因為要用複製constructor。
	MySpace::ViewPtr P1_monsterList_view(P1->getHoldMonsterView());
	P1_monsterList_view->setLeftTop(P1_ViewHoldMos_X, P1_ViewHoldMos_Y);
	this->P1_holdMonster_Displayer.registerView(P1_monsterList_view);

	MySpace::ViewPtr P2_monsterList_view(P2->getHoldMonsterView());
	P2_monsterList_view->setLeftTop(P2_ViewHoldMos_X, P2_ViewHoldMos_Y);
	this->P2_holdMonster_Displayer.registerView(P2_monsterList_view);

	// ===================== 
	// 對戰訊息
	MySpace::ViewPtr battleLog_view = myutil::createView('=', 6, 100);
	battleLog_view->setLeftTop(log_x, log_y);
	battleLog_view->print(2, " Nothing happens ");
	this->battle_log.registerView(battleLog_view);
	// ===================== 

	rlutil::cls();
	this->P1_DisplayerList[0].showRegisteredView();
	this->P1_holdMonster_Displayer.showRegisteredView();
	
	this->P2_DisplayerList[0].showRegisteredView();
	this->P2_holdMonster_Displayer.showRegisteredView();
	this->battle_log.showRegisteredView();
	rlutil::anykey(" wait... ");
}

void Jym::battle_start()
{
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
}
