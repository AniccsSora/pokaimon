#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include "MonsterProperty.h"

// pokemons.csv 存的位置。
#define monster_define_filePath "./assets/pokemons.csv"

// prototype
class IMonster;
class Monster;
class AttackBehavior;
class SkillBehavior;

typedef IMonster* IMonsterPtr;
typedef  Monster*  MonsterPtr;



class AttackBehavior
{
public:

	// 建構子
	AttackBehavior(IMonster& attacker);
	AttackBehavior();
	// ****************** 子類別可取用方法 *********************

	// 取得攻擊點數字串
	virtual const std::string getAtkStr();

	// 取得攻擊點數
	virtual const int getAtk();

	// 設定攻擊數值
	virtual void setAttack_point(int atkPoint);

	// 執行此攻擊，注意不是每個 怪物的攻擊都可以附加傷害。所以預設不動作。
	virtual void execute(IMonster& enemy);

	// 取得攻擊完成後的 資訊。
	virtual const std::string getAfterAttackMsg();

	// ******************************************************
protected:

	// 攻擊白值，沒有被防禦降低過的
	int attack_point = 0;

	// 攻擊 訊息。
	std::string atkMessage = "";

	// 代表攻擊者
	IMonster* attacker = NULL;

	// 攻擊轉字串訊息，前方會補空格。
	std::string d2str(int d);

	// 轉型用，如果轉型失敗直接跳例外。
	MonsterPtr trans2monsterPtr(IMonster& input);

};


// 普通攻擊，直接看自己的攻擊數值。
class NormalAttack : public AttackBehavior {

	// 建構子
	// 擁有基礎攻擊，im_attacker 代表攻擊者
	NormalAttack(IMonster& im_attacker);

	// 攻擊動作，會更新 atkMessage。
	virtual void execute(IMonster& enemy)override;
};



class SkillBehavior
{
public:
	// 建構子
	SkillBehavior(IMonster& attacker);
	SkillBehavior();
	// ****************** 子類別可取用方法 *********************

	// 執行此技能，注意不是每個 怪物的技能都有傷害。所以預設不動作。
	virtual void execute(IMonster& enemy); // 必定要覆寫，不設定 純虛擬 因為這樣不能持有此類別參照。

	// 取得攻擊完成後的 資訊。
	virtual const std::string getAfterSkillMsg();

	// 取得技能名稱
	virtual std::string getSkillName();

	// 技能 "已經" 使用的次數。
	virtual int useTimes();

	virtual bool is_attribute_defuff();
	// ******************************************************

	enum {
		HEAL = 1,
		BURNING,
		COUNTER_ATTACK,
		IMMUNOLOGY,
		LEECH_LIFE,
		AVOID,
		DOUBLE_ATTACK,
		POISON,
		LOWER_SPEED,
		ROCK_SKIN,
		LOWER_DEFENCE,
		LOWER_ATTACK
	};

protected:

	// 攻擊 訊息。
	std::string usedskillMsg = "";

	// 代表 技能使用者
	IMonster* attacker = NULL;

	// 攻擊轉字串訊息，前方會補空格。
	virtual std::string d2str(int d);

	// 轉型用，如果轉型失敗直接跳例外。
	virtual MonsterPtr trans2monsterPtr(IMonster input);

	// 技能使用次數， execute() 時才會 +1。
	int skillusedTimes = 0;

	// 是降低屬性 的 debuff;
	bool is_attribute_defuff_flg = false;
};

// 每回合回復HP3
class Skill_Heal : public SkillBehavior {
public:
	// 建構子
	Skill_Heal(IMonster& im_attacker);

	// 覆寫父類
	virtual void execute(IMonster& enemy)override;
};

// 隨機附加不受防禦影響的傷害1~3
class Skill_Burning : public SkillBehavior {
public:
	Skill_Burning(IMonster& im_attacker);

	virtual void execute(IMonster& enemy)override;
};

/*
templete

class templete: public SkillBehavior {
public:
	templete(IMonster& im_attacker);

	virtual void execute(IMonster& enemy)override;
};

*/

// 反擊1/5所受傷害
class Skill_Counter_Attack : public SkillBehavior {
public:
	Skill_Counter_Attack(IMonster& im_attacker);

	virtual void execute(IMonster& enemy)override;
};

// 免疫降低能力值的特殊能力
class Skill_Immunology : public SkillBehavior {
public:
	Skill_Immunology(IMonster& im_attacker);

	virtual void execute(IMonster& enemy)override;
};

// 使用後吸收2~3HP。
class Skill_Leech_Life : public SkillBehavior {
public:
	Skill_Leech_Life(IMonster& im_attacker);

	virtual void execute(IMonster& enemy)override;
};

class IMonster
{
public:

	friend class Jym;// 需要直接取得 Monster 的各個屬性作更動。
	friend class Skill_Heal;
	friend class Skill_Burning;
	friend class Skill_Counter_Attack;
	friend class Skill_Immunology;
	friend class Skill_Leech_Life;
	IMonster() = default;
	
protected:
	
	MonsterProperty property;
};

class Monster : public IMonster {
public:

	// 指定 monsterIdx 的怪物生成, 超出的去 idx 照樣生給你，就亂生。
	Monster(int monsterIdx, MonsterPropertyList mstPropertyList);

	// copy 建構子
	Monster(const Monster& mos);

	// 取得寵物在圖鑑上的編號
	int getIdx();

	std::string getName();

	monType getType();

	std::string getTypeStr();

	int getHp();

	int getAtk();

	int getDef();

	int getSpeed();

	int getAbilityIdx();

	// 寵物是否死亡?
	bool isDead();

	// 將 monster ability idx 轉成他的名字。
	std::string getAbilityNameByAbliIdx(int idx);
/*
	// 普通攻擊
	SkillToken attack(Monster& beAttactedMonster);

	// 使用技能
	SkillToken useSkill();
	
	// 處理敵人的攻擊，扣除自己的屬性 or 做 相對應的動作
	SkillToken processEnemyToken(SkillToken emyTk);
*/
	// 取得主人名
	std::string getMasterName();

	// 設定主人名
	void setMasterName(std::string masterName);

	// 設定遭遇敵人
	void setEnemy(IMonster& enemy);

	// 將敵人設定為 NULL 
	void setNoEnemy();

	// 取得敵人，如果沒有敵人，直接跳例外，阻止接下來的執行。
	IMonster& getEnemyInstance();

	// 該改 攻擊行為
	void setAttackBehavior(AttackBehavior& AB);

private:
	
	// 建構時給定。
	//Skill* skill = NULL;
	
	// 主人的名稱
	std::string masterName = "Undefined Master";

	// 敵人，因為可以直接修改參數，此怪物面對的敵人
	IMonster *encounterEnemy = nullptr;


   /*    
    *	Strategy Pattern: 在程式執行時才決定真正方法。
	*
	*   怪物的  "攻擊行為" & "技能行為" 有可能互相影響，
	*   也可能是獨立影響，也可能影響 A 不影響 S，反之；
	*   因為都不確定所以這邊就用 "行為" 來代替。
	*/

	// 平A攻擊行為。
	AttackBehavior *attackBehavior = nullptr;
	
	// 技能行為。
	SkillBehavior *skillBehavior = nullptr;

	// 被攻擊(attack)後的行為
	SkillBehavior *afterBeAttackedBehavior = nullptr;
};


struct NOT_EXIST_ENEMY : public std::exception {
	std::string s;
	NOT_EXIST_ENEMY(std::string ss) : s(ss) {}
	const char* what() const throw() { return s.c_str(); }
};

