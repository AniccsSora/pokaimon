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

	this->P1_hold_mosterN = P1->getMonsterListSize();
	this->P2_hold_mosterN = P2->getMonsterListSize();

	this->P1_canBattle_mon_idx = this->P1_hold_mosterN > 0 ? 0 : -1;
	this->P2_canBattle_mon_idx = this->P2_hold_mosterN > 0 ? 0 : -1;

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
		this->P1_ASCII_DList.push_back(*tmp_dis);
	}
	// 初始化 P2_DisplayerList
	for (size_t i = 0; i < P2->getMonsterListSize(); ++i) {
		int mos_idx = P2->getMonIDX_by_MonsList(i);// 從玩家物件 所持有的 monsterList 中去選我要第幾(i)個，怪物的圖鑑編號。 
		Displayer* tmp_dis = new Displayer();
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		mos->setLeftTop(P2_asciiView_X, P2_asciiView_Y);// 註冊View 前要 設定 LT。
		tmp_dis->registerView(mos);
		this->P2_ASCII_DList.push_back(*tmp_dis);
	}
	
	// 上方有幫每個 P1 ,Displayer 註冊 ASCII View，這邊要註冊 Monster Propterty View.
	for (size_t i = 0; i < this->P1_ASCII_DList.size(); ++i){
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
		Displayer* tmp_dis = new Displayer();//生一個暫存的 Displayer
		tmp_dis->registerView(property);
		this->P1_MProperty_DList.push_back(*tmp_dis);
	}
	
	// 上方有幫每個 P2 ,Displayer 註冊 ASCII View，這邊要註冊 Monster Propterty View.
	for (size_t i = 0; i < this->P2_ASCII_DList.size(); ++i) {
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
		Displayer* tmp_dis = new Displayer();//
		tmp_dis->registerView(property);
		this->P2_MProperty_DList.push_back(*tmp_dis);
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
	// 對戰訊息, 給定成 Jym 的成員變數，以利之後做 View的更動。
	// MySpace::ViewPtr battleLog_view = myutil::createView('=', 6, 100);
	this->battleLog_view->setLeftTop(log_x, log_y);
	this->battleLog_view->print(2, " Nothing happens ");
	this->battle_log.registerView(this->battleLog_view);
	// ===================== 

}

void Jym::battle_start()
{
	if (P1 == nullptr || P2 == nullptr) {
		return;
	}
	rlutil::cls();
	/*this->P1_ASCII_DList[0].showRegisteredView();
	this->P1_MProperty_DList[0].showRegisteredView();
	this->P1_holdMonster_Displayer.showRegisteredView();

	this->P2_ASCII_DList[0].showRegisteredView();
	this->P2_MProperty_DList[0].showRegisteredView();
	this->P2_holdMonster_Displayer.showRegisteredView();

	this->battle_log.showRegisteredView();*/

	// P1_canBattle_mon_idx 要更動。
	while (bothPlayerCanFight()){

		// 各 玩家 挑一隻出來
		MonsterPtr p1CurrentMons = pickCanBattleMonster(P1);
		MonsterPtr p2CurrentMons = pickCanBattleMonster(P2);
		cout << "====================== BATTLE ROUND ======================" << endl;
		cout << "P1: " << p1CurrentMons->getName() << endl;
		cout << "P2: " << p2CurrentMons->getName() << endl;
		while( bothMonsterCanFight(p1CurrentMons,p2CurrentMons) ){
			// 開始打架
			cout << " fack Battle LALALA~~~ " << endl;
			// P2 88
			p2CurrentMons->property.hp = 0;
			rlutil::anykey("wait to updatePropertyView()...");

			// 更新 View
			updatePropertyView();
			// Show PropertyVie.
			P1_MProperty_DList.at(P1_canBattle_mon_idx).showRegisteredView();
			P2_MProperty_DList.at(P2_canBattle_mon_idx).showRegisteredView();
			rlutil::anykey("wait to update paramater...");

			// 更新參數
			if (p1CurrentMons->getHp() <= 0) { P1_canBattle_mon_idx++; }
			if (p2CurrentMons->getHp() <= 0) { P2_canBattle_mon_idx++; }
			rlutil::anykey("wait to update log...");

			// 隨時更新
			this->battleLog_view->print(2, " P2:"+ p2CurrentMons->getName() + " Dead.");
			this->battle_log.showRegisteredView();
			rlutil::anykey("wait to next battle...");
			rlutil::cls();
		}

		// 更新 HoldMonster List
	}

	// 決定誰獲勝?

	
	rlutil::anykey(" wait... ");
}

bool Jym::bothPlayerCanFight()
{
	bool flg = false;

	// 可戰鬥的 指標 都 < 自身持有怪物的總數。 EX : 持有 3 隻怪，最大 idx 為 2， 但不得為三。
	if (P1_canBattle_mon_idx < P1_hold_mosterN &&
		P2_canBattle_mon_idx < P2_hold_mosterN) {
		flg = true;
	}
	return flg;
}

bool Jym::bothMonsterCanFight(MonsterPtr P1_mons, MonsterPtr P2_mons)
{
	bool flg = false;

	if (P1_mons->getHp() > 0 && P2_mons->getHp() > 0) {
		flg = true;
	}

	return flg;
}

void Jym::updatePropertyView(){

	// P1 新的 View。
	MySpace::ViewPtr property1 = myutil::createView('*', 13, 40);
	MonsterPtr mos1 = P1->getMonsterList().at(P1_canBattle_mon_idx);//剛剛在戰鬥的 idx

	// 資料寫入View
	property1->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
	property1->print(4, " ************************************ ");
	property1->print(5, "  Index - : " + std::to_string(mos1->getIdx()));
	property1->print(6, "  Name -- : " + mos1->getName());
	property1->print(7, "  Type -- : " + mos1->getTypeStr());
	property1->print(8, "  HP ---- : " + std::to_string(mos1->getHp()));
	property1->print(9, "  ATK --- : " + std::to_string(mos1->getAtk()));
	property1->print(10, "  DEF --- : " + std::to_string(mos1->getDef()));
	property1->print(11, "  SPEED - : " + std::to_string(mos1->getSpeed()));
	property1->print(12, "  Ability : " + mos1->getAbilityNameByAbliIdx(mos1->getAbilityIdx()));
	
	property1->setLeftTop(P1_pp_view_X, P1_pp_view_Y);// 設定 Property 座標
	// 用新的 View 去取代  P1_MProperty_DLis t現在的 idx 的 Displayer 的持有 View。
	this->P1_MProperty_DList.at(P1_canBattle_mon_idx).clearALLview();// 更新 Displayer。
	this->P1_MProperty_DList.at(P1_canBattle_mon_idx).registerView(property1);

	// =========== 更 新 P2
	// P2 新的 View。
	MySpace::ViewPtr property2 = myutil::createView('*', 13, 40);
	MonsterPtr mos2 = P2->getMonsterList().at(P2_canBattle_mon_idx);//剛剛在戰鬥的 idx

	// 資料寫入View
	property2->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
	property2->print(4, " ************************************ ");
	property2->print(5, "  Index - : " + std::to_string(mos2->getIdx()));
	property2->print(6, "  Name -- : " + mos2->getName());
	property2->print(7, "  Type -- : " + mos2->getTypeStr());
	property2->print(8, "  HP ---- : " + std::to_string(mos2->getHp()));
	property2->print(9, "  ATK --- : " + std::to_string(mos2->getAtk()));
	property2->print(10, "  DEF --- : " + std::to_string(mos2->getDef()));
	property2->print(11, "  SPEED - : " + std::to_string(mos2->getSpeed()));
	property2->print(12, "  Ability : " + mos2->getAbilityNameByAbliIdx(mos2->getAbilityIdx()));

	property2->setLeftTop(P2_pp_view_X, P2_pp_view_Y);// 設定 Property 座標
	// 用新的 View 去取代  P1_MProperty_DLis t現在的 idx 的 Displayer 的持有 View。
	this->P2_MProperty_DList.at(P2_canBattle_mon_idx).clearALLview();// 更新 Displayer。
	this->P2_MProperty_DList.at(P2_canBattle_mon_idx).registerView(property2);
}

MonsterPtr Jym::pickCanBattleMonster(PlayerPtr player)
{
	MonsterPtr chooseMonster = NULL;
	for (size_t i = 0; i < player->getMonsterListSize(); i++)
	{
		chooseMonster = player->monsterList.at(i);
		if (chooseMonster->getHp() > 0) {
			break;
		}
	}

	// 要傳了, 做額外的檢查。
	if (chooseMonster != nullptr) {
		return chooseMonster;
	}
	else { // for 迴圈全部跑完但是沒有一隻怪物有 血量。
		rlutil::anykey("Exception happens : Jym.cpp,MUST RETURN NONE NULL MonsterPtr.");
		exit(987678);
		return MonsterPtr();
	}
}
