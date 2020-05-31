#include "Monster.h"
#include "iostream"



void Monster::attack(IMonsterPtr beAttactedMonster) {

		// YA 從父類繼承下的
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
