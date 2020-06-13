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
	this->MAX_HP = pp.MAX_HP;

	// 旗標設定
	// 特殊狀態 抗性，免疫降低能力值的特殊能力(ATK,DEF,SPEED)
	this->sk_Immun_propertyDebuff = pp.sk_Immun_propertyDebuff;

	// 是否可以迴避下次攻擊? 0 不能 1 可以。
	this->can_avoid_next_attack_flg = pp.can_avoid_next_attack_flg;

	// can double attack 旗標
	this->can_double_attack_flg = pp.can_double_attack_flg;

	// 免疫 最終傷害 值，意旨當準備要扣下去時，它可以抵擋的傷害量。
	this->immune_final_damage_amount = pp.immune_final_damage_amount;

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
	this->MAX_HP = mp.MAX_HP;

	// 旗標設定
	// 特殊狀態 抗性，免疫降低能力值的特殊能力(ATK,DEF,SPEED)
	this->sk_Immun_propertyDebuff = mp.sk_Immun_propertyDebuff;

	// 是否可以迴避下次攻擊? 0 不能 1 可以。
	this->can_avoid_next_attack_flg = mp.can_avoid_next_attack_flg;

	// can double attack 旗標
	this->can_double_attack_flg = mp.can_double_attack_flg;

	// 免疫 最終傷害 值，意旨當準備要扣下去時，它可以抵擋的傷害量。
	this->immune_final_damage_amount = mp.immune_final_damage_amount;
}


void MonsterProperty::reduceAbility(propertyType type, int reduce_value)
{
	if ( canReduceAbility() ) {
		if (type == HP ) {
			if (canAvoidNextAtk()) { 
				can_avoid_next_attack_flg = 0; //旗標重設為 0;
			}
			else {
				int actual_damage = reduce_value - this->immune_final_damage_amount;
				if (canDoubleAttackOnce()) {
					can_double_attack_flg = 0;
					this->hp -= actual_damage;
					this->hp -= actual_damage;
				}
				else {
					this->hp -= actual_damage;
				}
				
			}
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

void MonsterProperty::reduceDirectly(propertyType type, int reduce_value)
{
	if (type == HP) {
		this->hp -= reduce_value;
	}
	else if (type == ATK) {
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
