#pragma once
#include <string>
#include "Mydefine.h"

// hardcode(order) by AsciiPokeGo.xlsx ...
enum monType{
	Undefined = -1,
	Normal,
	Fire,
	Water,
	Electric,
	Grass,
	Ice,
	Fighting,
	Poison,
	Ground,
	Flying,
	Psychic,
	Bug,
	Rock,
	Ghost,
	Dragon,
	Dark,
	Steel,
	Fairy
};

// 能力數值代號
enum propertyType {
	UNK = -1,
	HP,
	ATK,
	DEF,
	SPEED,
};

// 例外類別
class UNKNOW_propertyType : public std::exception {
public:
	propertyType type = propertyType::UNK;

	// 建構子
	UNKNOW_propertyType(propertyType type) {
		this->type = type;
	}

	virtual const char* what() const throw()
	{
		return std::string("UNKNOW_propertyType" + std::to_string(type)).c_str();
	}
};

class Property {
public:

	// 統一用此方法來降低 "能力數值"。
	// @ type: 要降低的屬性。
	// @ reduce_value: 要降低多少數值。
	virtual void reduceAbility(propertyType type, int reduce_value) = 0;
	
	// 統一用此方法來增加 "能力數值"。
	// @ type: 要增加 的屬性。
	// @ reduce_value: 要增加多少數值。
	virtual void increaseAbility(propertyType type, int increase_value) = 0;

	// 使此怪獸不會被降能力
	void set_sk_Immun_propertyDebuff_isTrue() {
		this->sk_Immun_propertyDebuff = 1;
	}

protected:
	// 這邊的參數 是給 怪物與怪物 之間 技能互動所用到的私有變數，如果沒有用到 都會是 -1。
	// 並且由多個 私有函式 幫助確認。(檢查 ability)

	// 特殊狀態 抗性，免疫降低能力值的特殊能力(HP,ATK,DEF,SPEED, )
	int sk_Immun_propertyDebuff = -1;

	// 使否可以降低能力。
	bool canReduceAbility() {
		if (sk_Immun_propertyDebuff <= 0) {
			return true;
		}
		else { return false; }
	}
};

class MonsterProperty :	public Property{
public:

	// Jym 需要直接做 參數操作。
	friend class Jym;

	MonsterProperty* operator=(MonsterProperty& pp);
	MonsterProperty() = default; // compile 說我沒寫預設建構子，好 我寫給他。
	MonsterProperty(int idx, std::string name, std::string type, int hp, int atk, int def, int speed, int ability) 
		:Property (){
		// 這裡沒 this 就是吃屎。直接不會動。
		this->idx = idx;
		this->name = name;
		this->type = str2type(type);
		this->typeStr = type;
		this->hp = hp;
		this->atk = atk;
		this->def = def;
		this->speed = speed;
		this->ability = ability;
	}

	MonsterProperty(const MonsterProperty& mp);

	int getIdx() {
		return idx;
	}
	void setIdx(int idx) {
		this->idx = idx;
	}

	std::string getName() {
		return name;
	}
	void setName(std::string name) {
		this->name = name;
	}

	monType getType() {
		return type;
	}
	void setType(monType type) {
		this->type = type;
	}

	std::string getTypeStr() {
		return typeStr;
	}
	void setTypeStr(std::string typeStr) {
		this->typeStr = typeStr;
	}

	int getHp() {
		return hp;
	}
	void setHp(int hp) {
		this->hp = hp;
	}

	int getAtk() {
		return atk;
	}
	void setAtk(int atk) {
		this->atk = atk;
	}

	int getDef() {
		return def;
	}
	void setDef(int def) {
		this->def = def;
	}

	int getSpeed() {
		return speed;
	}
	void setSpeed(int speed) {
		this->speed = speed;
	}

	// this idx is 1-base;
	int getAbilityIdx() {
		return ability;
	}
	void setAbilityIdx(int abilityIdx) {
		this->ability = abilityIdx;
	}

	// debug 用的
	void printALL() {
		std::string msg = "idx:" + std::to_string(idx) +
			", name: " + name +
			", type: " + std::to_string(type) +
			", hp: " + std::to_string(hp) +
			", atk: " + std::to_string(atk) +
			", def: " + std::to_string(def) +
			", speed: " + std::to_string(speed) +
			", ability: " + std::to_string(ability);
		std::cout << msg << std::endl;
	}

	// enum 土炮轉字串...
	monType str2type(std::string typeStr) {
		monType rtnType = Undefined;
		
		// 大寫版的 type 字串。
		std::string typeUpper = "";

		//  toupper 是給字元用的...，改成給字串用的版本
		for (auto& c : typeStr) { typeUpper += toupper(c);}
		
		// When equal compare() return 0.
		if (!std::string("NORMAL").compare(typeUpper)) {
			rtnType = Normal;
		}
		else if (!std::string("FIRE").compare(typeUpper)) {
			rtnType = Fire;
		}
		else if (!std::string("WATER").compare(typeUpper)) {
			rtnType = Water;
		}
		else if (!std::string("ELECTRIC").compare(typeUpper)) {
			rtnType = Electric;
		}
		else if (!std::string("GRASS").compare(typeUpper)) {
			rtnType = Grass;
		}
		else if (!std::string("ICE").compare(typeUpper)) {
			rtnType = Ice;
		}
		else if (!std::string("FIGHTING").compare(typeUpper)) {
			rtnType = Fighting;
		}
		else if (!std::string("POISON").compare(typeUpper)) {
			rtnType = Poison;
		}
		else if (!std::string("GROUND").compare(typeUpper)) {
			rtnType = Ground;
		}
		else if (!std::string("FLYING").compare(typeUpper)) {
			rtnType = Flying;
		}
		else if (!std::string("PSYCHIC").compare(typeUpper)) {
			rtnType = Psychic;
		}
		else if (!std::string("BUG").compare(typeUpper)) {
			rtnType = Bug;
		}
		else if (!std::string("ROCK").compare(typeUpper)) {
			rtnType = Rock;
		}
		else if (!std::string("GHOST").compare(typeUpper)) {
			rtnType = Ghost;
		}
		else if (!std::string("DRAGON").compare(typeUpper)) {
			rtnType = Dragon;
		}
		else if (!std::string("DARK").compare(typeUpper)) {
			rtnType = Dark;
		}
		else if (!std::string("STEEL").compare(typeUpper)) {
			rtnType = Steel;
		}
		else if (!std::string("FAIRY").compare(typeUpper)) {
			rtnType = Fairy;
		}
		else {
			std::cout << "UNHANDLE ENUM \'monType\': " << "\"" << typeUpper << "\"" << std::endl;
			std::system("pause");
			std::exit(8740);
		} 
		
		return rtnType;
	}

	// 降低指定數值
	void reduceAbility(propertyType type, int reduce_value)override;

	void  increaseAbility(propertyType type, int increase_value)override;

private:
	int idx = -1;
	std::string name = "";
	monType type = monType::Undefined;
	std::string typeStr = "";

	int hp = -1;
	int atk = -1;
	int def = -1;
	int speed = -1;
	int ability = -1;

};

typedef MySpace::Vec_1D_<MonsterProperty*> MonsterPropertyList;

