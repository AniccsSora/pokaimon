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
	//this->battleLog_view->print(2, " Nothing happens ");
	this->battle_log.registerView(this->battleLog_view);
	// ===================== 
	battleLog_view->setViewName("Battle log view [這是一段隨機的中文]");

	// 屬性相剋提示表View, 設定 位置。
	this->type_table_view->setLeftTop(type_table_x, type_table_y);
	this->type_table_view->setframeColor(rlutil::LIGHTBLUE);
	// 將屬性表 view 註冊進 他的 displayer.
	this->type_table_displayer.registerView(this->type_table_view);

}

void Jym::battle_start()
{
	// 最後 log 的開頭空白。
	std::string margin_of_log = std::string(50, ' ');
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
	// 雙方玩家都擁有可以戰鬥的寵物。
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
		
		// 雙方 挑一隻出來
		MonsterPtr p1CurrentMons = pickCanBattleMonster(P1);
		MonsterPtr p2CurrentMons = pickCanBattleMonster(P2);

		// 讓他們互相認親，知道要打的敵人是誰。
		p1CurrentMons->setEnemy(*p2CurrentMons);
		p2CurrentMons->setEnemy(*p1CurrentMons);

		// 初始化 陣列，由速度值高的先攻擊，所以放置到 陣列[0] 的位置。
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
			
			// 清空 log View 訊息。
			clearLog();
			// 重設游標至可印訊息處。 For log control.
			resetlogCursor();
			
			// 每個小回合確認 兩方怪物 速度
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
			
			// 關於屬性相剋計算:，在對打時 一律無視任何防禦減免、技能免疫，攻擊都先相乘到 atk上面。
			// 取得 0 -> 1 的，攻擊比率。
			atkRatio0x1 = lookup_AtkRatio(fight_list.at(0), fight_list.at(1), typeTable);
			// 取得 1 -> 0 的，攻擊比率。
			atkRatio1x0 = lookup_AtkRatio(fight_list.at(1), fight_list.at(0), typeTable);
			
			// 0->1 、 1->0， 倍率值 字串版本 變數宣告
			std::string atkRatio0x1_str = std::to_string(atkRatio0x1);
			std::string atkRatio1x0_str = std::to_string(atkRatio1x0);
			// 消除 字串版本的 0 尾數。 "1.00000" -> "1"
			atkRatio0x1_str.erase(atkRatio0x1_str.find_last_not_of('0') + 1, std::string::npos);
			atkRatio0x1_str.erase(atkRatio0x1_str.find_last_not_of('.') + 1, std::string::npos);
			// 消除 字串版本的 0 尾數。 "1.00000" -> "1"
			atkRatio1x0_str.erase(atkRatio1x0_str.find_last_not_of('0') + 1, std::string::npos);
			atkRatio1x0_str.erase(atkRatio1x0_str.find_last_not_of('.') + 1, std::string::npos);

			// 取用此變數是因為 P1 的怪物一定在左邊，不會因為 fight_list[0 1] 左邊改變。
			updateTypeTable(p1CurrentMons, p2CurrentMons);
			// 印出 屬性相剋表
			this->type_table_displayer.showRegisteredView();

			// 開始打架
			// battle_log_title 訊息
			std::string battle_log_title = "";
			// 更新 title 訊息，告知誰先(0一定先，但是要拿到名字)攻擊。
			battle_log_title = std::string(30, ' ') + "Round " + std::to_string(round_cnt) + " ,  " +
				fight_list[0]->getName() + " first attack. ";
			// 印 log 的 title 訊息
			this->battleLog_view->print(log_title_idx, battle_log_title);
			// 把 Title 印到 log View 上
			showlog();
			
			// 打架摟~
			// 速度高的怪獸 先攻擊

			// 如果回合不等於 代表 剛剛 [1] 有執行攻擊 ，所以這邊要多叫被動
			if (round_cnt != 1) {
				// 觸發後攻擊的人被動 (如果該怪物沒有被動技能，則他的 被動執行完時 msg 將會是空的)
				if ("" != fight_list[0]->getExeAfterBeAttackedBehaviorMessage()) {
					fight_list[0]->exeAfterBeAttackedBehavior();
					this->battleLog_view->print(getNextlineIdx(), getMargin() + fight_list[0]->getExeAfterBeAttackedBehaviorMessage());
					// 印 log 的 title 訊息
					this->battleLog_view->print_c(log_end_idx, margin_of_log +
						fight_list[0]->getName() + " triggered it passive " + fight_list[0]->getSkName()+ ".", rlutil::LIGHTGREEN);
					showlog(); rlutil::anykey("");
				}
			}

			// 提示區域 提醒使用者 [0] 要先攻擊 [1]
			this->battleLog_view->print_c(log_end_idx, margin_of_log + 
				" Press anykey let " + 
				            fight_list[0]->getMasterName() + "'s " + fight_list[0]->getName() + " attack " +
							fight_list[1]->getMasterName() + "'s " + fight_list[1]->getName()+".", rlutil::LIGHTCYAN);
			// 顯示 log
			showlog();
			// 等待 使用者反應
			rlutil::anykey();
			
			// 怪獸[0]攻擊
			fight_list[0]->exeAttackBehavior();
			
			// 更新 log 資料。
			this->battleLog_view->print(getNextlineIdx(), getMargin() + fight_list[0]->getExeAttackBehaviorMessage());
			// 顯示 log
			showlog();
			
			// 更新 Property View
			updatePropertyView();
			// Show PropertyView.
			P1_MProperty_DList.at(P1_canBattle_mon_idx).showRegisteredView();
			P2_MProperty_DList.at(P2_canBattle_mon_idx).showRegisteredView();

			// 提示區域 提醒使用者 [1] 被攻擊了
			this->battleLog_view->print_c(log_end_idx, margin_of_log + fight_list[1]->getName() +
				" is attacked by " + fight_list[0]->getName(), rlutil::LIGHTRED);
			// 顯示 log
			showlog();
			
			// 等待 使用者反應
			rlutil::anykey();
			
			// 提示區域 提醒使用者 [0] 要對 [1] 使用技能。
			this->battleLog_view->print_c(log_end_idx, margin_of_log + " Press anykey let " + fight_list[0]->getName() +
				" use skills against " + fight_list[1]->getName() + ".", rlutil::LIGHTCYAN);
			// 顯示 log
			showlog();
			
			// 等待 使用者反應
			rlutil::anykey();
			
			// 怪獸[0]使用技能
			fight_list[0]->exeSkillBehavior();
			
			// 更新 log 資料。
			this->battleLog_view->print(getNextlineIdx(), getMargin() + fight_list[0]->getExeSkillBehaviorMessage());
			// 更新 log 顯示
			showlog(); 
			
			// 更新 Property View
			updatePropertyView();
			// Show PropertyView.
			P1_MProperty_DList.at(P1_canBattle_mon_idx).showRegisteredView();
			P2_MProperty_DList.at(P2_canBattle_mon_idx).showRegisteredView();

			// 提示區域 提醒使用者 [1] 被 [0] 的技能影響了。
			this->battleLog_view->print_c(log_end_idx, margin_of_log + fight_list[1]->getName() +
				" is affected by " + fight_list[0]->getName() + "'s skill: " + fight_list[0]->getSkName() +".", rlutil::LIGHTRED);
			// 更新 log 顯示
			showlog();
			// 等待 使用者反應
			rlutil::anykey();

			//--------------------------
			// 提示區域 提醒使用者
			this->battleLog_view->print_c(log_end_idx, margin_of_log + " The next monster "+ fight_list[1]->getName() +
				" is about to attack.", rlutil::LIGHTCYAN);
			showlog();
			rlutil::anykey();
			
			// ==================== 因為 有一方打完了，要確定另一方沒有死才繼續戰鬥 ===================

			// 如果有人葛屁
			if (!bothMonsterCanFight(fight_list[0], fight_list[1])) {
				// 死掉的那方
				MonsterPtr deadOne = nullptr;
				//  更新參數
				if (p1CurrentMons->getHp() <= 0) {
					P1_canBattle_mon_idx++; 
					deadOne = p1CurrentMons;
				}
				if (p2CurrentMons->getHp() <= 0) { 
					P2_canBattle_mon_idx++; 
					deadOne = p2CurrentMons;
				}
				this->battleLog_view->print(log_end_idx, margin_of_log + deadOne->getName() + " is dead, press anykey to continue...");
				showlog();
				rlutil::anykey();

				// 一輪提早結束
				round_cnt++; //更新回合數
				break;
			}

			// 繼續 P2 的回合----------------------------------

			// 觸發 後攻擊的人被動 (如果該怪物沒有被動技能，則他的 被動執行完時 msg 將會是空的)
			fight_list[1]->exeAfterBeAttackedBehavior();
			if ("" != fight_list[1]->getExeAfterBeAttackedBehaviorMessage()) {
				this->battleLog_view->print(getNextlineIdx(), getMargin() + fight_list[1]->getExeAfterBeAttackedBehaviorMessage());
				this->battleLog_view->print_c(log_end_idx, margin_of_log +
				fight_list[1]->getName() + " triggered it passive " + fight_list[1]->getSkName() + ".", rlutil::LIGHTGREEN);
				// 印出 log
				showlog();
				// 等待使用者反應
				rlutil::anykey("");
			}
			
			//----------------------------------------
			/*
			// 提示區域 提醒使用者 [1] 要攻擊 [0]
			this->battleLog_view->print_c(log_end_idx, margin_of_log +
				" Press anykey let " +
				fight_list[1]->getMasterName() + "'s " + fight_list[1]->getName() + " attack " +
				fight_list[0]->getMasterName() + "'s " + fight_list[0]->getName() + ".", rlutil::LIGHTCYAN);
			// 顯示 log
			showlog();
			// 等待 使用者反應
			rlutil::anykey();
			*/

			// 怪獸[1]攻擊
			fight_list[1]->exeAttackBehavior();

			// 更新 log 資料。
			this->battleLog_view->print(getNextlineIdx(), getMargin() + fight_list[1]->getExeAttackBehaviorMessage());
			// 顯示 log
			showlog();

			// 更新 Property View
			updatePropertyView();
			// Show PropertyView.
			P1_MProperty_DList.at(P1_canBattle_mon_idx).showRegisteredView();
			P2_MProperty_DList.at(P2_canBattle_mon_idx).showRegisteredView();

			// 提示區域 提醒使用者 [0] 被攻擊了
			this->battleLog_view->print_c(log_end_idx, margin_of_log + fight_list[0]->getName() +
				" is attacked by " + fight_list[1]->getName(), rlutil::LIGHTRED);
			// 顯示 log
			showlog();

			// 等待 使用者反應
			rlutil::anykey();

			// 提示區域 提醒使用者 [1] 要對 [0] 使用技能。
			this->battleLog_view->print_c(log_end_idx, margin_of_log + " Press anykey let " + fight_list[1]->getName() +
				" use skills against " + fight_list[0]->getName() + ".", rlutil::LIGHTCYAN);
			// 顯示 log
			showlog();

			// 等待 使用者反應
			rlutil::anykey();

			// 怪獸[1]使用技能
			fight_list[1]->exeSkillBehavior();

			// 更新 log 資料。
			this->battleLog_view->print(getNextlineIdx(), getMargin() + fight_list[1]->getExeSkillBehaviorMessage());
			// 更新 log 顯示
			showlog();

			// 更新 Property View
			updatePropertyView();
			// Show PropertyView.
			P1_MProperty_DList.at(P1_canBattle_mon_idx).showRegisteredView();
			P2_MProperty_DList.at(P2_canBattle_mon_idx).showRegisteredView();

			// 提示區域 提醒使用者 [1] 使用了技能
			this->battleLog_view->print_c(log_end_idx, margin_of_log + fight_list[1]->getName() +
				" used the skill " +  fight_list[1]->getSkName() + ".", rlutil::LIGHTRED);
			// 更新 log 顯示
			showlog();
			// 等待 使用者反應
			rlutil::anykey();
			//----------
			
			// ------------ 一輪打完了
			// 更新參數, 確認有無人死亡

			// ==================== 兩方打完了，要確定另一方沒有死才繼續戰鬥 ===================

			// 如果有人葛屁
			if (!bothMonsterCanFight(fight_list[0], fight_list[1])) {
				// 死掉的那方
				MonsterPtr deadOne = nullptr;
				//  更新參數
				if (p1CurrentMons->getHp() <= 0) {
					P1_canBattle_mon_idx++;
					deadOne = p1CurrentMons;
				}
				if (p2CurrentMons->getHp() <= 0) {
					P2_canBattle_mon_idx++;
					deadOne = p2CurrentMons;
				}
				this->battleLog_view->print(log_end_idx, margin_of_log + deadOne->getName() + " is dead, press anykey to continue...");
				showlog();
				rlutil::anykey();

				// 一輪提早結束
				round_cnt++; //更新回合數
				break;
			}

			// 更新 log 並告訴戰鬥結果
			this->battleLog_view->print(getNextlineIdx(), getMargin() + " Round " + std::to_string(round_cnt) + " finish! ");
			this->battleLog_view->print(log_end_idx, margin_of_log + " Press anykey to next Round...");
			showlog();
			rlutil::anykey();
			// 一輪正式結束
			round_cnt++; //更新回合數
		}

		// 有一方 怪獸先死去。
		// 取消認親
		fight_list[0]->setNoEnemy();
		fight_list[1]->setNoEnemy();

		// 勝利的 monster idx，判斷 其中一位的 HP 即可
		int winner_idx = fight_list[0]->getHp() <= 0 ? 1:0;
		
		this->battleLog_view->print(getNextlineIdx(), getMargin() +
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
	std::string whoWin = "";
	if (P1_canBattle_mon_idx < P1_hold_mosterN) {
		// 勝利數量 ++。
		P1->addPoint();
		whoWin = P1->getName(); // P1 是玩家
	}
	else {
		whoWin = P2->getName(); // P1 是玩家
	}
	std::cout.flush();
	rlutil::anykey( whoWin + " is winner , P1's Point: " + std::to_string(P1->getPoint()) + ".");
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

std::string Jym::getMargin()
{
	return std::string(log_margin_f, ' ');
}

int Jym::getNextlineIdx()
{
	// 如果未初始化則代表第一次呼叫
	if (log_row_cursor < 0) { 

		log_row_cursor = log_start_row;
		return log_row_cursor;

	}
	else {

		// 指標先移動
		log_row_cursor += (log_stride + 1);
		// 防止 游標超出 logRowSize。
		int next = log_row_cursor % logRowSize;
		// 如果小於 起始位置，則一律回到起始位置。
		next = next < log_start_row ? 4 : next;
		// 回傳
		return next;
	}

}

void Jym::resetlogCursor()
{
	log_row_cursor = -1;
}

void Jym::updateTypeTable(MonsterPtr L, MonsterPtr R)
{
	// 先清乾淨
	for (size_t i = 1; i < type_table_h+1; ++i) {
		this->type_table_view->print(i, std::string(type_table_w,' '));
	}
	// 取得屬性相剋表，屬性的 攻擊倍率就是用這個表查表找的。
	// 取得相剋表
	TypeTable typeTable = myutil::getDamageRatioTable();
	// 查表語法 。A -> B， A打B時的倍率。
	// typeTable.at(A->getType()).at(B->getType());

	// 簡化查表 呼叫，at 來 at 去太複雜了。lambda function.
	auto lookup_AtkRatio = [](MonsterPtr A, MonsterPtr B, TypeTable t) {
		return t.at(A->getType()).at(B->getType());
	};
	
	// 取得 0 -> 1 的，攻擊比率。
	double atkRatioLxR = lookup_AtkRatio(L, R, typeTable);
	// 取得 1 -> 0 的，攻擊比率。
	double atkRatioRxL = lookup_AtkRatio(R, L, typeTable);

	// 0->1 、 1->0 字串的版本 變數宣告
	std::string atkRatioLxR_str = std::to_string(atkRatioLxR);
	std::string atkRatioRxL_str = std::to_string(atkRatioRxL);
	// 消除 字串版本的 0 尾數。 "1.00000" -> "1"
	atkRatioLxR_str.erase(atkRatioLxR_str.find_last_not_of('0') + 1, std::string::npos);
	atkRatioLxR_str.erase(atkRatioLxR_str.find_last_not_of('.') + 1, std::string::npos);
	// 消除 字串版本的 0 尾數。 "1.00000" -> "1"
	atkRatioRxL_str.erase(atkRatioRxL_str.find_last_not_of('0') + 1, std::string::npos);
	atkRatioRxL_str.erase(atkRatioRxL_str.find_last_not_of('.') + 1, std::string::npos);

	std::string  LtypeOrigin = L->getTypeStr();
	std::string  RtypeOrigin = R->getTypeStr();
	// 固定取前三個英文字當作 屬性字串
	std::string Ltype = std::string(LtypeOrigin.begin(), LtypeOrigin.begin() + 3);
	std::string Rtype = std::string(RtypeOrigin.begin(), RtypeOrigin.begin() + 3);
	// 開頭轉大寫
	Ltype[0] = std::toupper(Ltype[0]);
	Rtype[0] = std::toupper(Rtype[0]);

	// 準備要印上去的 資訊
	std::string msg1 = "    " + Ltype + " --- " + atkRatioLxR_str  + " ---> " + Rtype;
	std::string msg2 = "    " + Ltype + " <--- " + atkRatioRxL_str + " --- " + Rtype;

	// 不同倍率給予不同顏色
	if (atkRatioLxR > 1.0)
		this->type_table_view->print_c(2, msg1, rlutil::LIGHTGREEN);
	else if (atkRatioLxR < 1.0)
		this->type_table_view->print_c(2, msg1, rlutil::LIGHTRED);
	else
		this->type_table_view->print(2, msg1); // 預設白

	if (atkRatioRxL > 1.0)
		this->type_table_view->print_c(4, msg2, rlutil::LIGHTGREEN);
	else if (atkRatioRxL < 1.0)
		this->type_table_view->print_c(4, msg2, rlutil::LIGHTRED);
	else
		this->type_table_view->print(4, msg2); // 預設白
	
}
