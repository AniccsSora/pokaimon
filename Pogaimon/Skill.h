#pragma once
#include "MonsterProperty.h"

// --------------------------------------------- < class Prototype>
// 技能 基底類別
class Skill;

// 1-base
enum skillType {
	HEAL = 1,
	BURNING,
	COUNTER_ATTACK,
	IMMUNOLOGY,
	LEECH_LIFE,
	AVOID,
	DOUBLE_ATTACK,
	POISON,
	LOWER_SPEED,
	ROCK_SKIN,
	LOWER_DEFENCE,
	LOWER_ATTACK
}; // If add new type of this enum, please edit "Monster.cpp" constructor.

// 實際技能
class Heal;
class Burning;
class Counter_Attack;
class Immunology;
class Leech_Life;
class Avoid;
class Double_Attack;
class Poison;
class Lower_Speed;
class Rock_Skin;
class Lower_Defence;
class Lower_Attack;

// Monster::useSkill() 所會回傳的物件，這個不是技能
class SkillToken;
// --------------------------------------------- </class Prototype>

