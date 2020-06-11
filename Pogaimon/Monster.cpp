#include "Monster.h"
#include "iostream"



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

SkillToken Monster::attack(Monster& beAttactedMonster)
{
	SkillToken* rtnSkillToken;

	// 計算造成傷害
	int causeDamage = this->getAtk() - beAttactedMonster.getDef();

	// 造成敵人的 HP 下降。
	beAttactedMonster.property.reduceAbility(HP, causeDamage);

	std::string msg = this->getName() + " caused " + std::to_string(causeDamage) 
									  + " damage to " + beAttactedMonster.getName();

	// 本來會扣寫 但是這邊已經 扣完了，所以不用 再把旗標設為 YES_XXX
	rtnSkillToken = new SkillToken("attack", msg, NO, HP, 0);

	return *rtnSkillToken;
}

SkillToken Monster::useSkill()
{
	SkillToken *rtnSkillToken = new  SkillToken();
	
	this->skill->use();

	return *rtnSkillToken;
}

SkillToken Monster::processEnemyToken(SkillToken emyTk)
{
	SkillToken* rtnSkillToken = new  SkillToken();

	// 可以對其他怪獸造成影響。
	if (emyTk.canCauseOtherMonsterInfluence() != 0) {
		// 造成 負影響。
		if (emyTk.canCauseOtherMonsterInfluence() < 0 ){
			this->property.reduceAbility(emyTk.get_influence_property(), emyTk.get_influence_value());
		}
		// 造成 正影響。
		else {
			this->property.increaseAbility(emyTk.get_influence_property(), emyTk.get_influence_value());
		}
	}

	// 拼 token

	return *rtnSkillToken;
}

std::string Monster::getMasterName()
{
	return this->masterName;
}

void Monster::setMasterName(std::string masterName)
{
	this->masterName = masterName;
}
