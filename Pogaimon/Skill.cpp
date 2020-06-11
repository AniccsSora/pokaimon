#include "Skill.h"
#include <string>
#include <ctime>

#define YES_INCREASE 1
#define NO 0
#define YES_DECREASE -1

// Monster::useSkill() 所會回傳的物件，這個不是技能
class SkillToken {
public:

	// 建構子
	// @skname: 使用的技能名稱。
	// @msg: 使用技能後的訊息。
	// @canCauseOtherMonsterInfluence: 此 token 是否可以造成其他怪物影響。
	// 
	//  ~ canCauseOtherMonsterInfluence 不為 false 時，以下兩個參數才有意義。 ~ 
	// @influence_property: 造成哪一類影響。
	// @influence_value: 影響的數值。
	SkillToken(std::string skname, std::string msg, int canCauseOtherMonsterInfluence
		, propertyType influence_property, int influence_value) {

		this->skname = skname;
		this->msg = msg;
		this->canCauseOtherMonsterInfluence_F = canCauseOtherMonsterInfluence;
		this->influence_property = influence_property;
		this->influence_value = influence_value;
	}
	SkillToken() = default;

	// 回傳使用技能後的訊息
	std::string getUsedMsg() { return std::string(this->msg); }

	//此 token 是否可以造成其他怪物影響
	int canCauseOtherMonsterInfluence() { return canCauseOtherMonsterInfluence_F; }

	// 會被影響的屬性
	propertyType get_influence_property() { return this->influence_property; }

	int get_influence_value() { return this->influence_value; }

private:

	// 使用的技能名稱
	std::string skname = "Default skill name";

	// 使用技能後的訊息
	std::string msg = "Default message";

	// 此 token 是否可以造成其他怪物影響， 0代表不能，1代表正影響，-1代表負影響。
	int canCauseOtherMonsterInfluence_F = NO;

	// 如果  可以造成影響，那是哪一類?
	propertyType influence_property = UNK;

	// 那影響數值是多少
	int influence_value = 0;
};

// 技能 基底類別
class Skill {
public:
	Skill(MonsterProperty& pp) {
		this->pp = pp;
		this->skillName = getSKname();
	}

	// 主動技能
	virtual void use() = 0;

	// 被攻擊後所觸發的技能
	virtual void beAttacked() = 0;

	std::string getSKmsg() { return this->skillMsg; };

protected:

	// 當沒有此動作時，就是生成空 token。
	virtual SkillToken getEmptyToken() {
		return SkillToken("", "", false, HP, 0);
	}

	MonsterProperty pp;
	std::string skillName = "defalult name";

	// use() 後 才會有 msg 生成。
	std::string skillMsg = "defalult msg";

	// 呼叫 use() 後 才會指定。
	SkillToken st;

	int skillUsedTimes = 0;

private:

	// 取得 技能名稱。建構式會執行此 function.
	std::string getSKname() {
		if (HEAL == pp.getAbilityIdx()) {
			//this->skillName = "Heal";
			return "Heal";
		}
		else if(BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Burning";
			return "Burning";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Counter Attack";
			return "Counter Attack";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Immunology";
			return "Immunology";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Leech Life";
			return "Leech Life";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Avoid";
			return "Avoid";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Double Attack";
			return "Double Attack";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Poison";
			return "Poison";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Lower Speed";
			return "Lower Speed";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Rock Skin";
			return "Rock Skin";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Lower Defence";
			return "Lower Defence";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Lower Attack";
			return "Lower Attack";
		}
		else {
			//this->skillName = "Not defined skill name";
			return "Not defined skill name";
		}
	}
};

//每回合回復HP3
class SK_Heal : public Skill {
public:
	// 建構子
	SK_Heal(MonsterProperty& pp):Skill(pp){};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		pp.increaseAbility(HP, 3);
		// 製造 token
		this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		this->st = getEmptyToken();
	}
};

//隨機附加不受防禦影響的傷害1~3
class SK_Burning : public Skill {
public:
	// 建構子
	SK_Burning(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 生成 攻擊數值
		int exDamege = (rand() % 3) + 1;
		
		// 使用技能後訊息
		std::string point; // 決定是否要用複數型態。
		point = exDamege > 1 ? " points" : " point";
		this->skillMsg = "Caused extra " + std::to_string(exDamege) + point + " damege.";
		
		// 製造 token
		this->st = SkillToken(this->skillName, this->skillMsg, YES_DECREASE, HP, exDamege);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		// 製造 token
		this->st = getEmptyToken();
	}
};

//反擊 1/5 所受傷害
class SK_Counter_Attack : public Skill {
public:
	// 建構子
	SK_Counter_Attack(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 別人沒有攻擊你你不應該用 主動技能，所以 技能名字應該就是 ""空字串。
		this->st = getEmptyToken();
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		;
	}
};

//免疫降低能力值的特殊能力
class SK_Immunology : public Skill {
public:
	// 建構子
	SK_Immunology(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//每次攻擊吸收2~3HP
class SK_Leech_Life : public Skill {
public:
	// 建構子
	SK_Leech_Life(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//1 / 5機率迴避攻擊
class SK_Avoid : public Skill {
public:
	// 建構子
	SK_Avoid(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//1 / 5機率兩次攻擊
class SK_Double_Attack : public Skill {
public:
	// 建構子
	SK_Double_Attack(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//被攻擊的敵方中毒每回合 - 2HP(一場只發動一次, 產生影響的下一回合開始計算，持續2回合)
class SK_Poison : public Skill {
public:
	// 建構子
	SK_Poison(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//攻擊時降低敵方速度值2(一場只發動一次, 產生影響的下一回合開始計算，持續2回合)
class SK_Lower_Speed : public Skill {
public:
	// 建構子
	SK_Lower_Speed(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//每次受到的傷害 - 2
class SK_Rock_Skin : public Skill {
public:
	// 建構子
	SK_Rock_Skin(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//攻擊時降低敵方防禦力2(一場只發動一次, 產生影響的下一回合開始計算，持續2回合)
class SK_Lower_Defence : public Skill {
public:
	// 建構子
	SK_Lower_Defence(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//攻擊時降低敵方攻擊力2(一場只發動一次, 產生影響的下一回合開始計算，持續2回合)
class SK_Lower_Attack : public Skill {
public:
	// 建構子
	SK_Lower_Attack(MonsterProperty& pp) :Skill(pp) {};
	// 覆寫父類別
	virtual void use()override {
		// 使用技能後訊息
		//this->skillMsg = "heal 3 hp.";
		// 更改實際 數值
		//pp.increaseAbility(HP, 3);
		// 製造 token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// 覆寫父類別 被攻擊時所觸發的技能
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

