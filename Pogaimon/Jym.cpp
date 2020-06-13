#include "Jym.h"
#include <algorithm>

Jym::Jym(Player& P1, Player &P2)
{
	// P1(玩家如果沒有抓半隻怪獸就進去道館 叫他去吃屎)
	if (P1.getMonsterListSize() <= 0) {
		rlutil::cls();
		rlutil::anykey("\n\n     You don't seem to have any Monster. Are you going to fight boxing?     ");
		return;
	}

	this->P1_hold_mosterN = P1.getMonsterListSize();
	this->P2_hold_mosterN = P2.getMonsterListSize();

	this->P1_canBattle_mon_idx = this->P1_hold_mosterN > 0 ? 0 : -1;
	this->P2_canBattle_mon_idx = this->P2_hold_mosterN > 0 ? 0 : -1;

	// 初始化
	this->P1 = &P1;
	this->P2 = &P2;

	// 初始化 P1_DisplayerList (裡面存著 ascii View Displayer; 不同的 view 不同的 Displayer)
	for (size_t i = 0; i < P1.getMonsterListSize(); ++i) {
		int mos_idx = P1.getMonIDX_by_MonsList(i);// 從玩家物件 所持有的 monsterList 中去選我要第幾(i)個，怪物的圖鑑編號。 
		Displayer* tmp_dis = new Displayer();
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		mos->setLeftTop(P1_asciiView_X, P1_asciiView_Y);// 註冊View 前要 設定 LT。
		tmp_dis->registerView(mos);
		this->P1_ASCII_DList.push_back(*tmp_dis);
	}
	// 初始化 P2_DisplayerList
	for (size_t i = 0; i < P2.getMonsterListSize(); ++i) {
		int mos_idx = P2.getMonIDX_by_MonsList(i);// 從玩家物件 所持有的 monsterList 中去選我要第幾(i)個，怪物的圖鑑編號。 
		Displayer* tmp_dis = new Displayer();
		MySpace::ViewPtr mos = myutil::getMonsterASCIIViewPtrbyIdx(mos_idx);
		mos->setLeftTop(P2_asciiView_X, P2_asciiView_Y);// 註冊View 前要 設定 LT。
		tmp_dis->registerView(mos);
		this->P2_ASCII_DList.push_back(*tmp_dis);
	}
	
	// 上方有幫每個 P1 ,Displayer 註冊 ASCII View，這邊要註冊 Monster Propterty View.
	for (size_t i = 0; i < this->P1_ASCII_DList.size(); ++i){
		MySpace::ViewPtr property = myutil::createView('*', 13, 40);
		property->setViewName("P1 's Monster Propterty View.的辣");
		MonsterPtr mos = P1.getMonsterList().at(i);//取得一隻怪獸

		// 資料寫入View
		property->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
		property->print(4, " ************************************ ");
		property->print(5, "  Index - : " + std::to_string(mos->getIdx()));
		property->print(6, "  Name -- : " + mos->getName());
		property->print(7, "  Type -- : " + mos->getTypeStr());
		std::string HP_msg = std::to_string(mos->getHp()) + " / " + std::to_string(mos->getMAX_HP());
		property->print(8, std::string("  HP ---- : " + HP_msg));
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
		property->setViewName("P2 's Monster Propterty View.的辣");
		MonsterPtr mos = P2.getMonsterList().at(i);//取得一隻怪獸

		// 資料寫入View
		property->print(2, " ~~~~~~~~  Monater Property  ~~~~~~~~ ");
		property->print(4, " ************************************ ");
		property->print(5, "  Index - : " + std::to_string(mos->getIdx()));
		property->print(6, "  Name -- : " + mos->getName());
		property->print(7, "  Type -- : " + mos->getTypeStr());
		std::string HP_msg = std::to_string(mos->getHp()) + " / " + std::to_string(mos->getMAX_HP());
		property->print(8, std::string("  HP ---- : " + HP_msg));
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
	MySpace::ViewPtr P1_monsterList_view(P1.getHoldMonsterView());
	P1_monsterList_view->setLeftTop(P1_ViewHoldMos_X, P1_ViewHoldMos_Y);
	this->P1_holdMonster_Displayer.registerView(P1_monsterList_view);

	MySpace::ViewPtr P2_monsterList_view(P2.getHoldMonsterView());
	P2_monsterList_view->setLeftTop(P2_ViewHoldMos_X, P2_ViewHoldMos_Y);
	this->P2_holdMonster_Displayer.registerView(P2_monsterList_view);

	// ===================== 
	// 對戰訊息, 給定成 Jym 的成員變數，以利之後做 View的更動。
	// MySpace::ViewPtr battleLog_view = myutil::createView('=', 6, 100);
	this->battleLog_view->setLeftTop(log_x, log_y);
	this->battleLog_view->print(2, " Nothing happens ");
	this->battle_log.registerView(this->battleLog_view);
	// ===================== 
	battleLog_view->setViewName("Battle log view [這是一段隨機的中文]");
}

void Jym::battle_start()
{
	// 最後 log 的開頭空白。
	std::string margin = std::string(50, ' ');
	if (P1 == nullptr || P2 == nullptr) {
		return;
	}
	rlutil::cls();

	/*
	this->P1_ASCII_DList[0].showRegisteredView();
	this->P1_MProperty_DList[0].showRegisteredView();
	this->P1_holdMonster_Displayer.showRegisteredView();

	this->P2_ASCII_DList[0].showRegisteredView();
	this->P2_MProperty_DList[0].showRegisteredView();
	this->P2_holdMonster_Displayer.showRegisteredView();

	this->battle_log.showRegisteredView();
	*/

	// 決定誰先後攻擊，把變數放到 list 而已，0 數字越小越先攻擊。
	MySpace::Vec_1D_<MonsterPtr> fight_list;

	// 取得屬性相剋表，屬性的 攻擊倍率就是用這個表查表找的。
	// 取得相剋表
	TypeTable typeTable = myutil::getDamageRatioTable();
	// 查表語法 。A -> B， A打B時的倍率。
	// typeTable.at(A->getType()).at(B->getType());
	
	// 簡化查表 呼叫，at 來 at 去太複雜了。lambda function.
	auto lookup_AtkRatio = [](MonsterPtr A, MonsterPtr B, TypeTable t) {
		return t.at(A->getType()).at(B->getType());
	};

	// ------------------------------------------

	// P1_canBattle_mon_idx 要更動。
	while (bothPlayerCanFight()){
		// 清空怪獸暫存。
		fight_list.clear();
		// View 給他印出來。
		// 印出 ASCII color。
		this->P1_ASCII_DList[P1_canBattle_mon_idx].showRegisteredView();
		this->P2_ASCII_DList[P2_canBattle_mon_idx].showRegisteredView();
		// 印出 寵物屬性
		this->P1_MProperty_DList[P1_canBattle_mon_idx].showRegisteredView();
		this->P2_MProperty_DList[P2_canBattle_mon_idx].showRegisteredView();
		// 印出 持有寵物列表
		this->P1_holdMonster_Displayer.showRegisteredView();
		this->P2_holdMonster_Displayer.showRegisteredView();
		// 印出 Battle log, 這是簡化呼叫。因為log 會常常更新。
		showlog();
		
		// 各 玩家 挑一隻出來
		MonsterPtr p1CurrentMons = pickCanBattleMonster(P1);
		MonsterPtr p2CurrentMons = pickCanBattleMonster(P2);

		// 讓他們互相認親，知道要打的敵人是誰。
		p1CurrentMons->setEnemy(*p2CurrentMons);
		p2CurrentMons->setEnemy(*p1CurrentMons);

		// 修改 battle_log_view
		std::string battle_log_title = "";
		battle_log_title = std::string(3, ' ') + std::string(50, '=')+ " BATTLE LOG " + std::string(50, '=') + " ";
		this->battleLog_view->print(1, battle_log_title);
		
		showlog();

		// 初始化 陣列
		if (p1CurrentMons->property->getSpeed() >= p2CurrentMons->property->getSpeed()) {
			fight_list.push_back(p1CurrentMons); fight_list.push_back(p2CurrentMons);
		}
		else {
			fight_list.push_back(p2CurrentMons); fight_list.push_back(p1CurrentMons);
		}

		int round_cnt = 1;// 回合計數
		double atkRatio0x1 = .0;// 攻擊倍率 0 打 1 的
		double atkRatio1x0 = .0;// 攻擊倍率 1 打 0 的
		// 如果雙方可以打架
		while( bothMonsterCanFight(fight_list[0], fight_list[1]) ){
			// 重新確認 兩者速度
			if (fight_list[0]->property->getSpeed() >= fight_list[1]->property->getSpeed()) {
				; // 保持原樣
			}
			else {
				// 0: 給速度快的 monster;
				MonsterPtr tmp = fight_list[1];
				fight_list.at(0) = tmp;
				tmp              = fight_list.at(1);
				fight_list.at(1) = fight_list.at(0);
			}
			
			// 關於 比率攻擊，在對打時 無視任何防禦減免、技能免疫，攻擊都先相乘到 atk上面。
			// 取得 0 -> 1 的，攻擊比率。
			atkRatio0x1 = lookup_AtkRatio(fight_list.at(0), fight_list.at(1), typeTable);
			// 取得 1 -> 0 的，攻擊比率。
			atkRatio1x0 = lookup_AtkRatio(fight_list.at(1), fight_list.at(0), typeTable);
			
			// 在 setEenemy() 時 就可以設定倍率了。
			//設定 0 的攻擊比率。
			//fight_list.at(0)->setAtk_Ratio(atkRatio0x1);
			// 設定 1 的攻擊比率。
			//fight_list.at(1)->setAtk_Ratio(atkRatio1x0);
			
			// 0->1 、 1->0 字串的版本 變數宣告
			std::string atkRatio0x1_str = std::to_string(atkRatio0x1);
			std::string atkRatio1x0_str = std::to_string(atkRatio1x0);
			// 消除 字串版本的 0 尾數。 "1.00000" -> "1"
			atkRatio0x1_str.erase(atkRatio0x1_str.find_last_not_of('0') + 1, std::string::npos);
			atkRatio0x1_str.erase(atkRatio0x1_str.find_last_not_of('.') + 1, std::string::npos);
			// 消除 字串版本的 0 尾數。 "1.00000" -> "1"
			atkRatio1x0_str.erase(atkRatio1x0_str.find_last_not_of('0') + 1, std::string::npos);
			atkRatio1x0_str.erase(atkRatio1x0_str.find_last_not_of('.') + 1, std::string::npos);

			// 開始打架
			// 更新 title 訊息，告知誰先(0一定先，但是要拿到名字)攻擊。
			battle_log_title = std::string(30, ' ') + "Round " + std::to_string(round_cnt) + " ,  " +
				fight_list[0]->getName() + " first attack. ";
			// 補上 0 -> 1 攻擊倍率訊息
			battle_log_title += (std::string(5, ' ') + fight_list[0]->getName() + " -> " + fight_list[1]->getName() +
				" [ attack ratio : " + atkRatio0x1_str + " ]");
			// 更新 log 訊息
			this->battleLog_view->print(1, battle_log_title);
			
			
			// 打架摟~
			// 速度高的怪獸 先攻擊

			// 如果回合不等於 代表 剛剛 [1] 有執行攻擊 ，所以這邊要多叫被動
			if (round_cnt != 1) {
				fight_list[0]->exeAfterBeAttackedBehavior();
				this->battleLog_view->print(4, fight_list[0]->getExeAfterBeAttackedBehaviorMessage());
				showlog(); rlutil::anykey(" 4");
			}
			// 先攻擊
			fight_list[0]->exeAttackBehavior();
			this->battleLog_view->print(2, "     " + fight_list[0]->getExeAttackBehaviorMessage());
			showlog(); rlutil::anykey(" 2");
			// 使用技能
			fight_list[0]->exeSkillBehavior();
			this->battleLog_view->print(3, fight_list[0]->getExeSkillBehaviorMessage());
			showlog(); rlutil::anykey(" 3");

			//--------------------------
			this->battleLog_view->print_c(9, margin + "  wait to update "+ fight_list[1]->getMasterName() +" Property View()...", rlutil::LIGHTCYAN);
			showlog(); rlutil::anykey(" 9");
			
			
			// 更新 Property View
			updatePropertyView();
			// Show PropertyView.
			P1_MProperty_DList.at(P1_canBattle_mon_idx).showRegisteredView();
			P2_MProperty_DList.at(P2_canBattle_mon_idx).showRegisteredView();
			this->battleLog_view->print(9, margin +" Paramater " + fight_list[1]->getMasterName() + " view updated !");
			showlog();
			rlutil::anykey(); 

			// 如果有人葛屁
			if (!bothMonsterCanFight(fight_list[0], fight_list[1])) {
				// 更新參數, 確認有無人死亡
				if (p1CurrentMons->getHp() <= 0) { P1_canBattle_mon_idx++; }
				if (p2CurrentMons->getHp() <= 0) { P2_canBattle_mon_idx++; }
				this->battleLog_view->print(9, margin + " wait to update log...");
				showlog();
				rlutil::anykey();

				// 更新 log 並告訴戰鬥結果
				this->battleLog_view->print(8, " Round " + std::to_string(round_cnt) + " finish! ");
				this->battleLog_view->print(9, margin + " wait to next Round...");
				showlog();
				rlutil::anykey();
				// 記得要清空 log View 訊息。
				clearLog();
				// 一輪提早結束
				round_cnt++; //更新回合數
				fight_list[0]->setAtk_Ratio_1();// 初始化 攻擊倍率
				fight_list[1]->setAtk_Ratio_1();// 初始化 攻擊倍率
				break;
			}

			// 繼續 P2 的回合----------------------------------


			// -------- 後攻擊的人

			// 觸發 後攻擊的人被動
			fight_list[1]->exeAfterBeAttackedBehavior();
			this->battleLog_view->print(5, fight_list[1]->getExeAfterBeAttackedBehaviorMessage());
			showlog(); 
			rlutil::anykey(" 5");
			
			// 後攻擊的人 攻擊
			fight_list[1]->exeAttackBehavior();
			this->battleLog_view->print(6, fight_list[1]->getExeAttackBehaviorMessage());
			showlog(); rlutil::anykey(" 6");
			// 後攻擊的人 使用技能
			fight_list[1]->exeSkillBehavior();
			this->battleLog_view->print(7, fight_list[1]->getExeSkillBehaviorMessage());
			showlog(); rlutil::anykey(" 7");

			this->battleLog_view->print_c(9, margin + "  wait to update " + fight_list[0]->getMasterName() + " Property View()...", rlutil::LIGHTCYAN);
			showlog();
			rlutil::anykey();
			
			// 更新 Property View
			updatePropertyView();
			// Show PropertyView.
			P1_MProperty_DList.at(P1_canBattle_mon_idx).showRegisteredView();
			P2_MProperty_DList.at(P2_canBattle_mon_idx).showRegisteredView();
			this->battleLog_view->print(9, margin + " Paramater " + fight_list[0]->getMasterName() + " view updated !");
			showlog();
			rlutil::anykey();

			// ------------ 一輪打完了
			// 更新參數, 確認有無人死亡
			if (p1CurrentMons->getHp() <= 0) { P1_canBattle_mon_idx++; }
			if (p2CurrentMons->getHp() <= 0) { P2_canBattle_mon_idx++; }
			this->battleLog_view->print(9, margin + " wait to update log...");
			showlog();
			rlutil::anykey(); 
			
			// 更新 log 並告訴戰鬥結果
			this->battleLog_view->print(8, " Round " + std::to_string(round_cnt) + " finish! ");
			this->battleLog_view->print(9, margin + " wait to next Round...");
			showlog();
			rlutil::anykey();
			// 記得要清空 log View 訊息。
			clearLog();
			// 一輪正式結束
			fight_list[0]->setAtk_Ratio_1();// 初始化 攻擊倍率
			fight_list[1]->setAtk_Ratio_1();// 初始化 攻擊倍率
			round_cnt++; //更新回合數
		}

		// 有一方 怪獸先死去。
		// 取消認親
		fight_list[0]->setNoEnemy();
		fight_list[1]->setNoEnemy();

		// 勝利的 monster idx
		int winner_idx = fight_list[0]->getHp() <= 0 ? 1:0;
		
		this->battleLog_view->print(9, std::string(10, ' ') +
			fight_list[0]->getName() + " v.s. "+ fight_list[1]->getName() + " battle End.  " +
			fight_list[winner_idx]->getMasterName() + "\'s Monster \"" + fight_list[winner_idx]->getName() + "\" is Winner");
		showlog();
		rlutil::anykey();
		rlutil::cls();
		// 更新 HoldMonster List 需要用到 顏色嗎?
	}// 雙方繼續戰鬥<loop>

	// 已有其中一方 不能戰鬥。
	// 決定誰獲勝? 隨便判定 P1 or P2 的參數就可以。 這邊用 P1判斷。
	// if 可以戰鬥的 monster idx < 持有總數 。 EX: 2 < 3。 
	if (P1_canBattle_mon_idx < P1_hold_mosterN) {
		// 勝利數量 ++, 注意 這邊的是 Player 副本。
		P1->addPoint();
	}

	std::cout.flush();
	rlutil::anykey(" Who win?? wait... P1's Point: " + std::to_string(P1->getPoint()) + ".");
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
	std::string HP_msg1 = std::to_string(mos1->getHp()) + " / " + std::to_string(mos1->getMAX_HP());
	property1->print(8, std::string("  HP ---- : " + HP_msg1));
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
	std::string HP_msg2 = std::to_string(mos2->getHp()) + " / " + std::to_string(mos2->getMAX_HP());
	property2->print(8,  std::string("  HP ---- : " + HP_msg2));
	property2->print(9, "  ATK --- : " + std::to_string(mos2->getAtk()));
	property2->print(10, "  DEF --- : " + std::to_string(mos2->getDef()));
	property2->print(11, "  SPEED - : " + std::to_string(mos2->getSpeed()));
	property2->print(12, "  Ability : " + mos2->getAbilityNameByAbliIdx(mos2->getAbilityIdx()));

	property2->setLeftTop(P2_pp_view_X, P2_pp_view_Y);// 設定 Property 座標
	// 用新的 View 去取代  P1_MProperty_DLis t現在的 idx 的 Displayer 的持有 View。
	this->P2_MProperty_DList.at(P2_canBattle_mon_idx).clearALLview();// 更新 Displayer。
	this->P2_MProperty_DList.at(P2_canBattle_mon_idx).registerView(property2);
}

void Jym::fight(MonsterPtr M1, MonsterPtr M2)
{
	//M1->property

	// 決定誰先後攻擊，把變數放到 list 而已，0 數字越小越先攻擊。
	MySpace::Vec_1D_<MonsterPtr> fight_list;

	if (M1->property->getSpeed() >= M2->property->getSpeed()) {
		fight_list.push_back(M1); fight_list.push_back(M2);
	}
	else {
		fight_list.push_back(M2); fight_list.push_back(M1);
	}

	// 打架摟~
	while ( bothMonsterCanFight(fight_list[0], fight_list[1]) ) {
		// 速度高的怪獸 先攻擊
		//SkillToken tk_0 = fight_list[0]->attack(*fight_list[1]);

		rlutil::anykey("Press anykey to next round");
	}


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

void Jym::showlog()
{
	this->battle_log.showRegisteredView();
}

inline void Jym::clearLog()
{
	for (size_t i = 1; i <= logRowSize; i++)
	{
		this->battleLog_view->print(i, std::string(logColSize, ' '));
	}
}
