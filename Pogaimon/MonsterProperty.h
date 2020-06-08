#pragma once
#include <string>
#include "Mydefine.h"

// hardcode by AsciiPokeGo.xlsx ...
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


class Property {

};

class MonsterProperty :	public Property{
public:

	// Jym 需要直接做 參數操作。
	friend class Jym;

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
			std::cout << "UNHANDLE ENUM : " << "\"" << typeUpper << "\"" << std::endl;
			std::system("pause");
			std::exit(8740);
		} 
		
		return rtnType;
	}
private:
	int idx = -1;
	std::string name = "";
	monType type = Undefined;
	std::string typeStr = "";
	int hp = -1;
	int atk = -1;
	int def = -1;
	int speed = -1;
	int ability = -1;
	
};

typedef MySpace::Vec_1D_<MonsterProperty*> MonsterPropertyList;

