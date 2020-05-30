#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "MonsterProperty.h"
#include <ctime>

// pokemons.csv �s����m�C
#define monster_define_filePath "./assets/pokemons.csv"

class IMonster;
typedef IMonster* IMonsterPtr;

class IMonster
{
public:
	IMonster() = default;
	

protected:
	// ���� beAttactedMonster.
	virtual void attack(IMonsterPtr beAttactedMonster) = 0; // pure virtual function
	MonsterProperty property;

};

class Monster : public IMonster {
public:
	
	// ���w monsterIdx ���Ǫ��ͦ�, �W�X���h idx �Ӽ˥͵��A�A�N�å͡C
	Monster(int monsterIdx, MonsterPropertyList mstPropertyList){
		// �B�z�W�X�h�� idx
		if (monsterIdx > mstPropertyList.size()-1) { // 0-base > 1-base
			monsterIdx = (monsterIdx+rand()) % mstPropertyList.size();
		}
		// �d�����s��
		property.setIdx(mstPropertyList.at(monsterIdx)->getIdx());

		// �d���W��
		property.setName(mstPropertyList.at(monsterIdx)->getName());

		// �ݩ�
		property.setType(mstPropertyList.at(monsterIdx)->getType());

		property.setHp(mstPropertyList.at(monsterIdx)->getHp());
		property.setAtk(mstPropertyList.at(monsterIdx)->getAtk());
		property.setDef(mstPropertyList.at(monsterIdx)->getDef());
		property.setSpeed(mstPropertyList.at(monsterIdx)->getSpeed());
		property.setAbilityIdx(mstPropertyList.at(monsterIdx)->getAbilityIdx());
	};
	
	void attack(IMonsterPtr beAttactedMonster);

	int getIdx();

	std::string getName();

	monType getType();

	int getHp();

	int getAtk();

	int getDef();

	int getSpeed();

	int getAbilityIdx();
	   
private:
	int aaa = 0;

	

};
typedef Monster* MonsterPtr;

