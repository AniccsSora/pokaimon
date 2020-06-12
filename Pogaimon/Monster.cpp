#include "Monster.h"
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

const std::string AttackBehavior::getAtkStr()
{
	return std::to_string(attack_point);
}

const int AttackBehavior::getAtk()
{
	return this->attack_point;
}

void AttackBehavior::setAttack_point(int atkPoint)
{
	this->attack_point = atkPoint;
}

void AttackBehavior::execute(IMonster& enemy)
{
	;// 預設 AttackBehavior 是不執行任何動作的。
}

const std::string AttackBehavior::getAfterAttackMsg()
{
	return atkMessage;
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
	MonsterPtr enemyMonsterPtr = trans2monsterPtr(im_attacker);

	// 更新攻擊力
	this->attack_point = enemyMonsterPtr->getAtk();
}

void NormalAttack::execute(IMonster& enemy)
{
	MonsterPtr enemyMonsterPtr = trans2monsterPtr(enemy);

	int damage = enemyMonsterPtr->getDef() - attack_point;

	// 造成 XXX ??? 傷害訊息。
	this->atkMessage = "cause " + enemyMonsterPtr->getName() + d2str(damage);

}
// **********************************************************  
//                             ------
// *********************  SkillBehavior(父) ******************  

SkillBehavior::SkillBehavior(IMonster& attacker)
{
	this->attacker = &attacker;
}

SkillBehavior::SkillBehavior()
{
}

void SkillBehavior::execute(IMonster& enemy)
{
	;// 預設 SkillBehavior 是不執行任何動作的。
}

const std::string SkillBehavior::getAfterSkillMsg()
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
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Counter Attack";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Immunology";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Leech Life";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Avoid";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Double Attack";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Poison";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Lower Speed";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Rock Skin";
	}
	else if (BURNING == mos.getAbilityIdx()) {
		skName = "Lower Defence";
	}
	else if (BURNING == mos.getAbilityIdx()) {
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
#pragma warning(disable:4172)
MonsterPtr SkillBehavior::trans2monsterPtr(IMonster input)
{
	MonsterPtr rtn = nullptr;
	try {
		rtn = static_cast<MonsterPtr>(&input);
	}
	catch (...) {
		std::cout << "\nbad_cast IMonster -> Monster cast failed." << std::endl;
	}
	return rtn;
	#pragma warning(default:4172)
}

// ***********************************************************  

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
	mos->property.increaseAbility(HP, 3);
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
	victim->property.reduceAbility(HP, ExDamage);

	// 拼 使用技能後的字串
	this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
		"\' caused " + victim->getName() + std::to_string(ExDamage) + " extra damage.";

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
	victim->property.reduceAbility(HP, damage);

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
	mos->property.set_sk_Immun_propertyDebuff_isTrue();

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
	if (victim->property.canAvoidNextAtk()) {
		// 已經迴避這次攻擊了，所以旗標歸0
		victim->property.setCanAvoidNextATK_FALSE();

		// 技能使用 miss
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\', but " + victim->getName() + " avoid this skill.";
	}
	else {
		// 2~3 點吸收 HP
		int suuHp = rand() % 2 + 2;
		mos->property.increaseAbility(HP, suuHp);
		// 拼 使用技能後的字串
		this->usedskillMsg = mos->getName() + " used skills \'" + getSkillName() +
			"\' heal " + std::to_string(suuHp) + " HP.";
	}

	this->skillusedTimes++;
}

// ***********************************************************

Monster::Monster(int monsterIdx, MonsterPropertyList mstPropertyList)
{
	
	// 處理超出去的 idx
	if (monsterIdx > mstPropertyList.size() - 1) { // 0-base > 1-base
		monsterIdx = (monsterIdx + rand()) % mstPropertyList.size();
	}
	// 寵物的編號
	property.setIdx(mstPropertyList.at(monsterIdx)->getIdx());

	// 寵物名稱
	property.setName(mstPropertyList.at(monsterIdx)->getName());

	// 屬性
	property.setType(mstPropertyList.at(monsterIdx)->getType());
	property.setTypeStr(mstPropertyList.at(monsterIdx)->getTypeStr());
	property.setHp(mstPropertyList.at(monsterIdx)->getHp());
	property.setAtk(mstPropertyList.at(monsterIdx)->getAtk());
	property.setDef(mstPropertyList.at(monsterIdx)->getDef());
	property.setSpeed(mstPropertyList.at(monsterIdx)->getSpeed());
	property.setAbilityIdx(mstPropertyList.at(monsterIdx)->getAbilityIdx());
	/*
	// 指定生成 何種 Skill 物件。
	if (property.getAbilityIdx() == skillType::HEAL) {
		this->skill = new SK_Heal(this->property);
	}
	else if (property.getAbilityIdx() == skillType::BURNING) {
		this->skill = new SK_Burning(this->property);
	}
	else if (property.getAbilityIdx() == skillType::COUNTER_ATTACK) {
		this->skill = new SK_Counter_Attack(this->property);
	}
	else if (property.getAbilityIdx() == skillType::IMMUNOLOGY) {
		// 特殊能力
		this->property.set_sk_Immun_propertyDebuff_isTrue();
		this->skill = new SK_Immunology(this->property);
	}
	else if (property.getAbilityIdx() == skillType::LEECH_LIFE) {
		this->skill = new SK_Leech_Life(this->property);
	}
	else if (property.getAbilityIdx() == skillType::AVOID) {
		this->skill = new SK_Avoid(this->property);
	}
	else if (property.getAbilityIdx() == skillType::DOUBLE_ATTACK) {
		this->skill = new SK_Double_Attack(this->property);
	}
	else if (property.getAbilityIdx() == skillType::POISON) {
		this->skill = new SK_Poison(this->property);
	}
	else if (property.getAbilityIdx() == skillType::LOWER_SPEED) {
		this->skill = new SK_Lower_Speed(this->property);
	}
	else if (property.getAbilityIdx() == skillType::ROCK_SKIN) {
		this->skill = new SK_Rock_Skin(this->property);
	}
	else if (property.getAbilityIdx() == skillType::LOWER_DEFENCE) {
		this->skill = new SK_Lower_Defence(this->property);
	}
	else if (property.getAbilityIdx() == skillType::LOWER_ATTACK) {
		this->skill = new SK_Lower_Attack(this->property);
	}
	else {
		rlutil::anykey(" Err(Monster.cpp): wrong skill initialize : property.getAbilityIdx()=\'" + std::to_string(property.getAbilityIdx()) + "\'");
		exit(887);
	}
	*/
}

Monster::Monster(const Monster& mos)
{
	if (this != &mos) {
		this->masterName = mos.masterName;
		MonsterProperty* mp = new MonsterProperty(mos.property);
		this->property = *mp;
	}
}

int Monster::getIdx() {
	return property.getIdx();
}


std::string Monster::getName() {
	return property.getName();
}


monType Monster::getType() {
	return property.getType();
}

std::string Monster::getTypeStr() {
	return property.getTypeStr();
}

int Monster::getHp() {
	return property.getHp();
}


int Monster::getAtk() {
	return property.getAtk();
}


int Monster::getDef() {
	return property.getDef();
}


int Monster::getSpeed() {
	return property.getSpeed();
}

int Monster::getAbilityIdx() {
	return property.getAbilityIdx();
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
}

void Monster::setNoEnemy()
{
	this->encounterEnemy = NULL;
}

IMonster& Monster::getEnemyInstance()
{
	if (this->encounterEnemy == nullptr)
		throw  NOT_EXIST_ENEMY("Does not exists enemy!");

	return *(this->encounterEnemy);
}

void Monster::setAttackBehavior(AttackBehavior& AB)
{
	this->attackBehavior = &AB;
}
