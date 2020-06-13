#include "Monster.h"
#include "Myutil.h"
#include "iostream"
#include <ctime>
#include <cmath>

// *********************  AttackBehavior(父) ******************  

AttackBehavior::AttackBehavior(IMonster& attacker)
{
	this->attacker = &attacker; 
}

AttackBehavior::AttackBehavior()
{
}

void AttackBehavior::execute(IMonster& enemy)
{
	;// 預設 AttackBehavior 是不執行任何動作的。
}

const std::string AttackBehavior::getExecutedMsg()
{
	return atkMessage;
}

void AttackBehavior::setAttacker(IMonster& attacker)
{
	this->attacker = &attacker;
}


std::string AttackBehavior::d2str(int d)
{
	if (d > 1) {
		return " " + std::to_string(d) + " damages.";
	}
	else {
		return " " + std::to_string(d) + " damage.";
	}
}

MonsterPtr AttackBehavior::trans2monsterPtr(IMonster& input)
{
	try {
		MonsterPtr rtn = static_cast<MonsterPtr>(&input);
		return rtn;
	}
	catch (...) {
		std::cout << "\nbad_cast IMonster -> Monster cast failed." << std::endl;
	}
}

// ************************************************************  

// *********************  NormalAttack(子) ******************  

NormalAttack::NormalAttack(IMonster& im_attacker) :AttackBehavior(im_attacker)
{
	// IMonster 先轉 Monster
	MonsterPtr mos = trans2monsterPtr(im_attacker);
}

const int NormalAttack::getFinalAtkByRatio(IMonster& enemy)
{
	// 攻擊者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 確認 mos所遇到的敵人指標。
	MonsterPtr m_enemy = trans2monsterPtr(enemy);

	// 取得攻擊倍率
	double r = mos->getAtk_Ratio();
	// 原始攻擊白值
	int atk = mos->getAtk();
	// 四捨五入最終結果
	return round(r * atk);
}

void NormalAttack::execute(IMonster& enemy)
{
	// 攻擊者
	MonsterPtr atker = trans2monsterPtr(*attacker);
	
	// 敵人
	MonsterPtr enemyMonsterPtr = trans2monsterPtr(enemy);

	// 對敵人造成的傷害
	int damage = getFinalAtkByRatio(enemy) - enemyMonsterPtr->getDef();

	if (damage < 0) {
		throw new CAUSE_MINUE_DAMAGE(damage);
	}


	// 造成 XXX ??? 傷害訊息。
	this->atkMessage = atker->getName() + " causes " + enemyMonsterPtr->getName() + d2str(damage);

	enemyMonsterPtr->property->reduceAbility(HP, damage);

}
// **********************************************************  
//                             ------
// *********************  SkillBehavior(父) ******************  

SkillBehavior::SkillBehavior(IMonster& attacker)
{
	this->attacker = &attacker;
}
/*
SkillBehavior::SkillBehavior()
{
}
*/
void SkillBehavior::execute(IMonster& enemy)
{
	;// 預設 SkillBehavior 是不執行任何動作的。
}

const std::string SkillBehavior::getExecutedMsg()
{
	return usedskillMsg;
}

std::string SkillBehavior::getSkillName()
{
	// 技能持有者
	Monster mos = *trans2monsterPtr(*attacker);

	// 回傳用
	std::string skName = "";

	if (HEAL == mos.getAbilityIdx()) {
		skName = "Heal";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Burning";
	}
	else if (COUNTER_ATTACK == mos.getAbilityIdx()) {
		skName = "Counter Attack";
	}
	else if (IMMUNOLOGY == mos.getAbilityIdx()) {
		skName = "Immunology";
	}
	else if (LEECH_LIFE == mos.getAbilityIdx()) {
		skName = "Leech Life";
	}
	else if (AVOID == mos.getAbilityIdx()) {
		skName = "Avoid";
	}
	else if (DOUBLE_ATTACK == mos.getAbilityIdx()) {
		skName = "Double Attack";
	}
	else if (POISON == mos.getAbilityIdx()) {
		skName = "Poison";
	}
	else if (LOWER_SPEED == mos.getAbilityIdx()) {
		skName = "Lower Speed";
	}
	else if (ROCK_SKIN == mos.getAbilityIdx()) {
		skName = "Rock Skin";
	}
	else if (LOWER_DEFENCE == mos.getAbilityIdx()) {
		skName = "Lower Defence";
	}
	else if (LOWER_ATTACK == mos.getAbilityIdx()) {
		skName = "Lower Attack";
	}
	else {
		skName = "Not defined skill name";
	}

	return skName;
}

int SkillBehavior::useTimes()
{
	return this->skillusedTimes;
}

void SkillBehavior::setAttacker(IMonster& attacker)
{
	this->attacker = &attacker;
}

bool SkillBehavior::is_attribute_defuff()
{
	return this->is_attribute_defuff_flg;
}

std::string SkillBehavior::d2str(int d)
{
	if (d > 1) {
		return " " + std::to_string(d) + " damages.";
	}
	else {
		return " " + std::to_string(d) + " damage.";
	}
}

MonsterPtr SkillBehavior::trans2monsterPtr(IMonster& input)
{
	try {
		MonsterPtr rtn = static_cast<MonsterPtr>(&input);
		return rtn;
	}
	catch (...) {
		std::cout << "\nbad_cast IMonster -> Monster cast failed." << std::endl;
	}
}

// ***********************************************************  

// *********************  NoneBehavior ****************** 

NoneBehavior::NoneBehavior(IMonster& im_attacker) : SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void NoneBehavior::execute(IMonster& enemy)
{
	;// 因為沒有行為所以不實作
	this->skillusedTimes++;
}

// ******************************************************

// *********************  Skill_Heal ******************  

Skill_Heal::Skill_Heal(IMonster& im_attacker) :SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Heal::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);

	// 要是 IMonster 的 friend 才能直接更動 property。

	// 實作技能
	mos->property->increaseAbility(HP, 3);
	// 拼 使用技能後的字串
	this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() + "\' cure 3 hp.";
	this->skillusedTimes++;
}

// ************************************************************* 

// *********************  Skill_Burning ******************  

Skill_Burning::Skill_Burning(IMonster& im_attacker) :SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Burning::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	// 要是 IMonster 的 friend 才能直接更動 property。

	// 實作技能
	// 製造 隨機攻擊
	int ExDamage = rand() % 3 + 1;
	// 直接降低
	victim->property->reduceDirectly(HP, ExDamage);

	// 拼 使用技能後的字串
	this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
		"\' caused " + victim->getName() + " " +std::to_string(ExDamage) + " extra damage.";

	this->skillusedTimes++;
}

// *******************************************************

// *********************  Skill_Counter_Attack ******************  
Skill_Counter_Attack::Skill_Counter_Attack(IMonster& im_attacker) :SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Counter_Attack::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	// 要是 IMonster 的 friend 才能直接更動 property。

	// 實作技能
	// 製造 被攻擊的 1/5(4捨5入).
	int damage = round((mos->getDef() - victim->getAtk()) / 5);
	victim->property->reduceAbility(HP, damage);

	// 拼 使用技能後的字串
	this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
		"\' caused " + victim->getName() + std::to_string(damage) + " extra damage.";

	this->skillusedTimes++;
}


// **************************************************************

// *********************  Skill_Counter_Attack ****************** 

Skill_Immunology::Skill_Immunology(IMonster& im_attacker) :SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Immunology::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	// 要是 IMonster 的 friend 才能直接更動 property。

	// 實作技能
	mos->property->set_sk_Immun_propertyDebuff_isTrue();

	// 拼 使用技能後的字串
	this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
		"\' it have immunity of " + victim->getName() + " reduction attribute skill";

	this->skillusedTimes++;
}

// **************************************************************

// *********************  Skill_Leech_Life ****************** 

Skill_Leech_Life::Skill_Leech_Life(IMonster& im_attacker) :SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Leech_Life::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	// 要是 IMonster 的 friend 才能直接更動 property。

	// 實作技能

	// 如果不能攻擊到 目標 則不能發動技能。
	if (victim->property->canAvoidNextAtk()) {
		// 已經迴避這次攻擊了，所以旗標歸0
		victim->property->setCanAvoidNextATK_FALSE();

		// 技能使用 miss
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\', but " + victim->getName() + " avoid this skill.";
	}
	else {
		// 2~3 點吸收 HP
		int suuHp = rand() % 2 + 2;
		mos->property->increaseAbility(HP, suuHp);
		// 拼 使用技能後的字串
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\' heal " + std::to_string(suuHp) + " HP.";
	}

	this->skillusedTimes++;
}

// **************************************************************

// *********************  Skill_Avoid ****************** 

Skill_Avoid::Skill_Avoid(IMonster& im_attacker) : SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Avoid::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	//MonsterPtr victim = trans2monsterPtr(enemy);

	// 要是 IMonster 的 friend 才能直接更動 property。

	// 實作技能
	if ( myutil::X_Probability_get_True(0.2) ) {
		mos->property->setCanAvoidNextATK();

		// 拼 使用技能後的字串
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\' success!";
		this->skillusedTimes++;
	}
	else {
		;// 技能沒觸發就不做事
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\' fail. ";
	}
	
}
// **************************************************************

// *********************  Double_Attack ****************** 

Skill_Double_Attack::Skill_Double_Attack(IMonster& im_attacker) : SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Double_Attack::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	//MonsterPtr victim = trans2monsterPtr(enemy);

	// 要是 IMonster 的 friend 才能直接更動 property。

	// 實作技能
	if (myutil::X_Probability_get_True(0.2)) {
		mos->property->setDoubleAttackOnce();

		// 拼 使用技能後的字串
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\' success!";
		this->skillusedTimes++;
	}
	else {
		;// 技能沒觸發就不做事
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\' fail. ";
	}

}

// *******************************************************

// *********************  Skill_Poison ****************** 
Skill_Poison::Skill_Poison(IMonster& im_attacker) : SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Poison::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	if (this->skillusedTimes == 0) {
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() + "\'";
	}
	else if (this->skillusedTimes < 2) {
		this->usedskillMsg = victim->getName() + " is poisoned, reduced by 2 HP.";
		victim->property->reduceDirectly(HP, 2);
	}
	else {
		this->usedskillMsg = "";
		;// 已經過了兩回合
	}

	this->skillusedTimes ++ ;
}

// *******************************************************

// *********************  Skill_Lower_Speed ****************** 
Skill_Lower_Speed::Skill_Lower_Speed(IMonster& im_attacker) : SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Lower_Speed::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	// 目標免疫
	if (victim->property->canImmun_propertyDebuff()) { 
		this->usedskillMsg = victim->getName() + " immune \'" + getSkillName() + "\' skill.";
	}
	// 目標可以降低速度
	else { 
		if (this->skillusedTimes == 0) {
			this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() + "\'";
		}
		else if (this->skillusedTimes < 2) {
			this->usedskillMsg = victim->getName() + " is solwed, reduced by 2 speed.";
			victim->property->reduceAbility(SPEED, 2);
		}
		else {
			this->usedskillMsg = "";
			;// 已經過了兩回合
		}
	}

	this->skillusedTimes++;
}
// *******************************************************

// *********************  Skill_Rock_Skin ****************** 
Skill_Rock_Skin::Skill_Rock_Skin(IMonster& im_attacker) : SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Rock_Skin::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	//MonsterPtr victim = trans2monsterPtr(enemy);

	// 技能實作
	mos->property->setImmune_final_damage_amount(2);
	
	// 技能使用後訊息
	this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
		 "\' damage taken reduced by 2.";
	
	this->skillusedTimes++;
}
// *******************************************************

// *********************  Skill_Lower_Defence ****************** 
Skill_Lower_Defence::Skill_Lower_Defence(IMonster& im_attacker): SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Lower_Defence::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	// 目標免疫
	if (victim->property->canImmun_propertyDebuff()) {
		this->usedskillMsg = victim->getName() + " immune \'" + getSkillName() + "\' skill.";
	}
	// 目標可以降低速度
	else {
		if (this->skillusedTimes == 0) {
			this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() + "\'";
		}
		else if (this->skillusedTimes < 2) {
			this->usedskillMsg = victim->getName() + " reduced by 2 defence.";
			victim->property->reduceAbility(DEF, 2);
		}
		else {
			this->usedskillMsg = "";
			;// 已經過了兩回合
		}
	}

	this->skillusedTimes++;
}
// ********************************************************** 

// *********************  Skill_Lower_Attack ****************** 
Skill_Lower_Attack::Skill_Lower_Attack(IMonster& im_attacker) : SkillBehavior(im_attacker)
{
	;// 用父建構 初始化即可
}

void Skill_Lower_Attack::execute(IMonster& enemy)
{
	// 技能使用者
	MonsterPtr mos = trans2monsterPtr(*attacker);
	// 被施法者
	MonsterPtr victim = trans2monsterPtr(enemy);

	// 目標免疫
	if (victim->property->canImmun_propertyDebuff()) {
		this->usedskillMsg = victim->getName() + " immune \'" + getSkillName() + "\' skill.";
	}
	// 目標可以降低速度
	else {
		if (this->skillusedTimes == 0) {
			this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() + "\'";
		}
		else if (this->skillusedTimes < 2) {
			this->usedskillMsg = victim->getName() + " reduced by 2 attack point.";
			victim->property->reduceAbility(ATK, 2);
		}
		else {
			this->usedskillMsg = "";
			;// 已經過了兩回合
		}
	}

	this->skillusedTimes++;
}
// *******************************************************

// ***********************************************************

Monster::Monster(int monsterIdx, MonsterPropertyList mstPropertyList)
{
	
	// 處理超出去的 idx
	if (monsterIdx > mstPropertyList.size() - 1) { // 0-base > 1-base
		monsterIdx = (monsterIdx + rand()) % mstPropertyList.size();
	}
	// IDX = monsterIdx 的寵物 property, p。
	MonsterProperty *p = mstPropertyList[monsterIdx];
	// 初始化 Monster::property
	this->property = new MonsterProperty(
		p->getIdx(),
		p->getName(),
		p->getTypeStr(),
		p->getHp(),
		p->getAtk(),
		p->getDef(),
		p->getSpeed(),
		p->getAbilityIdx());
	 
	// 設定最大 HP、跟攻擊比率在 MonsterProperty new 時就會 初始化。
	
	// 指定生成 何種 Skill 物件。
	if (property->getAbilityIdx() == SkillBehavior::HEAL) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Heal(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	
	else if (property->getAbilityIdx() == SkillBehavior::BURNING) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Burning(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::COUNTER_ATTACK) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new NoneBehavior(*this); // 注意 反擊不是主動技能
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new Skill_Counter_Attack(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::IMMUNOLOGY) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Immunology(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::LEECH_LIFE) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Leech_Life(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::AVOID) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Avoid(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::DOUBLE_ATTACK) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Double_Attack(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::POISON) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Poison(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::LOWER_SPEED) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Lower_Speed(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::ROCK_SKIN) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Rock_Skin(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::LOWER_DEFENCE) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Lower_Defence(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else if (property->getAbilityIdx() == SkillBehavior::LOWER_ATTACK) {
		// 給定 攻擊行為
		this->attackBehavior = new NormalAttack(*this);
		// 給定 技能行為
		this->skillBehavior = new Skill_Lower_Attack(*this);
		// 給定 被攻擊後的行為
		this->afterBeAttackedBehavior = new NoneBehavior(*this);
	}
	else {
		rlutil::anykey(" Err(Monster.cpp): wrong skill initialize : property->getAbilityIdx()=\'" + std::to_string(property->getAbilityIdx()) + "\'");
		exit(887);
	}

	// 幫所有行為的 attacker 都註冊為自己。
	this->attackBehavior->setAttacker(*this);
	this->skillBehavior->setAttacker(*this);
	this->afterBeAttackedBehavior->setAttacker(*this);

 	//rlutil::anykey();
}

Monster::Monster(const Monster& mos)
{
	if (this != &mos) {
		this->masterName = mos.masterName;

		//MonsterProperty* mp = new MonsterProperty(*(mos.property));
		this->property = mos.property;

		this->encounterEnemy = mos.encounterEnemy;

		// 複製 平A攻擊行為。
		this->attackBehavior = mos.attackBehavior;

		// 複製 技能行為。
		this->skillBehavior = mos.skillBehavior;

		// 複製  被攻擊(attack)後的行為
		this->afterBeAttackedBehavior = mos.afterBeAttackedBehavior;
	}
}

int Monster::getIdx() {
	return property->getIdx();
}


std::string Monster::getName() {
	return property->getName();
}


monType Monster::getType() {
	return property->getType();
}

std::string Monster::getTypeStr() {
	return property->getTypeStr();
}

int Monster::getHp() {
	return property->getHp();
}


int Monster::getAtk() {
	return property->getAtk();
}


int Monster::getDef() {
	return property->getDef();
}


int Monster::getSpeed() {
	return property->getSpeed();
}

int Monster::getAbilityIdx() {
	return property->getAbilityIdx();
}

int Monster::getMAX_HP()
{
	return property->getMAX_HP();
}

double Monster::getAtk_Ratio()
{
	return property->getATK_RATIO();
}

void Monster::setAtk_Ratio(double r)
{
	property->setATK_RATIO(r);
}

void Monster::setAtk_Ratio_1()
{
	property->setATK_RATIO(1.0);
}

bool Monster::isDead()
{
	bool flg = false;
	if (getHp() <= 0) {
		flg = true;
	}
	return flg;
}

std::string Monster::getAbilityNameByAbliIdx(int idx)
{
	std::string rtnName = "";

	switch (idx) {
	case 1:
		rtnName = "Heal";
		break;
	case 2:
		rtnName = "Burning";
		break;
	case 3:
		rtnName = "Counter Attack";
		break;
	case 4:
		rtnName = "Immunology";
		break;
	case 5:
		rtnName = "Leech Life";
		break;
	case 6:
		rtnName = "Avoid";
		break;
	case 7:
		rtnName = "Double Attack";
		break;
	case 8:
		rtnName = "Poison";
		break;
	case 9:
		rtnName = "Lower Speed";
		break;
	case 10:
		rtnName = "Rock Skin";
		break;
	case 11:
		rtnName = "Lower Defence";
		break;
	case 12:
		rtnName = "Lower Attack";
		break;
	default:
		rtnName = "Undefined SkName...";
	}

	return rtnName;
}

std::string Monster::getMasterName()
{
	return this->masterName;
}

void Monster::setMasterName(std::string masterName)
{
	this->masterName = masterName;
}

void Monster::setEnemy(IMonster& enemy)
{
	this->encounterEnemy = &enemy;
	// 在知道敵人是誰 就可以知道自己的倍率。
	
	// 取得相剋表
	TypeTable typeTable = myutil::getDamageRatioTable();
	// 取得屬性相剋表後，屬性的攻擊倍率就是用這個表查表找的。

	// 查表語法 。A -> B， A打B時的倍率。
	// typeTable.at(A->getType()).at(B->getType());

	// 簡化查表 呼叫，at 來 at 去太複雜了。lambda function.
	auto lookup_AtkRatio = [](MonsterPtr A, MonsterPtr B, TypeTable t) {
		return t.at(A->getType()).at(B->getType());
	};
	// 向下轉型 
	MonsterPtr m_enemy = static_cast<MonsterPtr>(&enemy);
	// 設定攻擊倍率
	this->setAtk_Ratio( lookup_AtkRatio(this, m_enemy, typeTable) );
}

void Monster::setNoEnemy()
{
	this->encounterEnemy = NULL;
}

IMonster& Monster::getEnemyInstance()
{
	// 指標為空?? (!NULL) => true，他就會丟例外。
	if (!this->encounterEnemy)
		throw  NOT_EXIST_ENEMY("Does not exists enemy!");

	return *(this->encounterEnemy);
}

void Monster::setAttackBehavior(AttackBehavior& AB)
{
	this->attackBehavior = &AB;
}

void Monster::exeAttackBehavior()
{
	this->attackBehavior->execute(this->getEnemyInstance());
}

void Monster::exeSkillBehavior()
{
	this->skillBehavior->execute(this->getEnemyInstance());
}

void Monster::exeAfterBeAttackedBehavior()
{
	this->afterBeAttackedBehavior->execute(this->getEnemyInstance());
}
std::string Monster::getExeAttackBehaviorMessage()
{
	return this->attackBehavior->getExecutedMsg();
}
std::string Monster::getExeSkillBehaviorMessage()
{
	return this->skillBehavior->getExecutedMsg();
}
std::string Monster::getExeAfterBeAttackedBehaviorMessage()
{
	return this->afterBeAttackedBehavior->getExecutedMsg();
}
//------------------------------------------------------
