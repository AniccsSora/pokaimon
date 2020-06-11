#pragma once
#include "MonsterProperty.h"

// --------------------------------------------- < class Prototype>
// �ޯ� �����O
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

// ��ڧޯ�
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

// Monster::useSkill() �ҷ|�^�Ǫ�����A�o�Ӥ��O�ޯ�
class SkillToken;
// --------------------------------------------- </class Prototype>

