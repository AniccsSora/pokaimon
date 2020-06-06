#include "MonsterProperty.h"

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
