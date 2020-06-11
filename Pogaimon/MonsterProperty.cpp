#include "MonsterProperty.h"

MonsterProperty* MonsterProperty::operator=(MonsterProperty& pp)
{
	this->idx = pp.idx;
	this->name = pp.name;
	this->type = pp.type;
	this->typeStr = pp.typeStr;
	this->hp = pp.hp;
	this->atk = pp.atk;
	this->def = pp.def;
	this->speed = pp.speed;
	this->ability = pp.ability;
	this->sk_Immun_propertyDebuff = pp.sk_Immun_propertyDebuff;
	this->sk_usedSkill_cnt = pp.sk_usedSkill_cnt;
	return this;
}

MonsterProperty::MonsterProperty(const MonsterProperty& mp){
	this->idx = mp.idx;
	this->name = mp.name;
	this->type = mp.type;
	this->typeStr = mp.typeStr;
	this->hp = mp.hp;
	this->atk = mp.atk;
	this->def = mp.def;
	this->speed = mp.speed;
	this->ability = mp.ability;
}


void MonsterProperty::reduceAbility(propertyType type, int reduce_value)
{
	if ( canReduceAbility() ) {
		if (type == HP) {
			this->hp -= reduce_value;
		}
		else if (type == ATK){
			this->atk -= reduce_value;
		}
		else if (type == DEF) {
			this->def -= reduce_value;
		}
		else if (type == SPEED) {
			this->speed -= reduce_value;
		}
		else {
			throw UNKNOW_propertyType(type);
		}
		return;
	}
	else {// 即使擁有 免疫降低能力值 之技能，HP 仍要可以被扣。
		if (type == HP) {
			this->hp -= reduce_value;
		}
		else {
			// 欲降低 HP以外的 指令都不會被執行...
			return;
		}
	}
}

void MonsterProperty::increaseAbility(propertyType type, int increase_value)
{
	if (type == HP) {
		this->hp += increase_value;
	}
	else if (type == ATK) {
		this->atk += increase_value;
	}
	else if (type == DEF) {
		this->def += increase_value;
	}
	else if (type == SPEED) {
		this->speed += increase_value;
	}
	else {
		throw UNKNOW_propertyType(type);
	}
	return;
}
