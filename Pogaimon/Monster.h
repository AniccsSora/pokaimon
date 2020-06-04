#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "MonsterProperty.h"
#include <ctime>

// pokemons.csv 存的位置。
#define monster_define_filePath "./assets/pokemons.csv"

class IMonster;
typedef IMonster* IMonsterPtr;

class IMonster
{
public:
	IMonster() = default;
	

protected:
	// 攻擊 beAttactedMonster.
	virtual void attack(IMonsterPtr beAttactedMonster) = 0; // pure virtual function
	MonsterProperty property;

};

class Monster : public IMonster {
public:
	
	// 指定 monsterIdx 的怪物生成, 超出的去 idx 照樣生給你，就亂生。
	Monster(int monsterIdx, MonsterPropertyList mstPropertyList){
		// 處理超出去的 idx
		if (monsterIdx > mstPropertyList.size()-1) { // 0-base > 1-base
			monsterIdx = (monsterIdx+rand()) % mstPropertyList.size();
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
	};

	void attack(IMonsterPtr beAttactedMonster);

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

	// 將 monster ability idx 轉成他的名字。
	std::string getAbilityNameByAbliIdx(int idx);
	   
private:
	int aaa = 0;

	

};
typedef Monster* MonsterPtr;

