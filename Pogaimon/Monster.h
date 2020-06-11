#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "MonsterProperty.h"
#include <ctime>
#include "Skill.cpp"

// pokemons.csv 存的位置。
#define monster_define_filePath "./assets/pokemons.csv"

class IMonster;
typedef IMonster* IMonsterPtr;

class IMonster
{
public:

	friend class Jym;// 需要直接取得 Monster 的各個屬性作更動。

	IMonster() = default;
	
protected:
	// 攻擊 beAttactedMonster.
	//virtual SkillToken attack(Monster& beAttactedMonster) = 0; // pure virtual function

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

	// 普通攻擊
	SkillToken attack(Monster& beAttactedMonster);

	// 使用技能
	SkillToken useSkill();
	
	// 處理敵人的攻擊，扣除自己的屬性 or 做 相對應的動作
	SkillToken processEnemyToken(SkillToken emyTk);
	
	// 取得主人名
	std::string getMasterName();

	// 設定主人名
	void setMasterName(std::string masterName);

private:
	int aaa = 0;

	// 建構時給定。
	Skill* skill = NULL;
	
	// 主人的名稱
	std::string masterName = "Undefined";
};

typedef Monster* MonsterPtr;

