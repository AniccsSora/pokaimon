#include "Skill.h"
#include <string>
#include <ctime>

#define YES_INCREASE 1
#define NO 0
#define YES_DECREASE -1

// Monster::useSkill() �ҷ|�^�Ǫ�����A�o�Ӥ��O�ޯ�
class SkillToken {
public:

	// �غc�l
	// @skname: �ϥΪ��ޯ�W�١C
	// @msg: �ϥΧޯ�᪺�T���C
	// @canCauseOtherMonsterInfluence: �� token �O�_�i�H�y����L�Ǫ��v�T�C
	// 
	//  ~ canCauseOtherMonsterInfluence ���� false �ɡA�H�U��ӰѼƤ~���N�q�C ~ 
	// @influence_property: �y�����@���v�T�C
	// @influence_value: �v�T���ƭȡC
	SkillToken(std::string skname, std::string msg, int canCauseOtherMonsterInfluence
		, propertyType influence_property, int influence_value) {

		this->skname = skname;
		this->msg = msg;
		this->canCauseOtherMonsterInfluence_F = canCauseOtherMonsterInfluence;
		this->influence_property = influence_property;
		this->influence_value = influence_value;
	}
	SkillToken() = default;

	// �^�ǨϥΧޯ�᪺�T��
	std::string getUsedMsg() { return std::string(this->msg); }

	//�� token �O�_�i�H�y����L�Ǫ��v�T
	int canCauseOtherMonsterInfluence() { return canCauseOtherMonsterInfluence_F; }

	// �|�Q�v�T���ݩ�
	propertyType get_influence_property() { return this->influence_property; }

	int get_influence_value() { return this->influence_value; }

private:

	// �ϥΪ��ޯ�W��
	std::string skname = "Default skill name";

	// �ϥΧޯ�᪺�T��
	std::string msg = "Default message";

	// �� token �O�_�i�H�y����L�Ǫ��v�T�A 0�N����A1�N���v�T�A-1�N��t�v�T�C
	int canCauseOtherMonsterInfluence_F = NO;

	// �p�G  �i�H�y���v�T�A���O���@��?
	propertyType influence_property = UNK;

	// ���v�T�ƭȬO�h��
	int influence_value = 0;
};

// �ޯ� �����O
class Skill {
public:
	Skill(MonsterProperty& pp) {
		this->pp = pp;
		this->skillName = getSKname();
	}

	// �D�ʧޯ�
	virtual void use() = 0;

	// �Q�������Ĳ�o���ޯ�
	virtual void beAttacked() = 0;

	std::string getSKmsg() { return this->skillMsg; };

protected:

	// ��S�����ʧ@�ɡA�N�O�ͦ��� token�C
	virtual SkillToken getEmptyToken() {
		return SkillToken("", "", false, HP, 0);
	}

	MonsterProperty pp;
	std::string skillName = "defalult name";

	// use() �� �~�|�� msg �ͦ��C
	std::string skillMsg = "defalult msg";

	// �I�s use() �� �~�|���w�C
	SkillToken st;

	int skillUsedTimes = 0;

private:

	// ���o �ޯ�W�١C�غc���|���榹 function.
	std::string getSKname() {
		if (HEAL == pp.getAbilityIdx()) {
			//this->skillName = "Heal";
			return "Heal";
		}
		else if(BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Burning";
			return "Burning";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Counter Attack";
			return "Counter Attack";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Immunology";
			return "Immunology";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Leech Life";
			return "Leech Life";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Avoid";
			return "Avoid";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Double Attack";
			return "Double Attack";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Poison";
			return "Poison";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Lower Speed";
			return "Lower Speed";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Rock Skin";
			return "Rock Skin";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Lower Defence";
			return "Lower Defence";
		}
		else if (BURNING == pp.getAbilityIdx()) {
			//this->skillName = "Lower Attack";
			return "Lower Attack";
		}
		else {
			//this->skillName = "Not defined skill name";
			return "Not defined skill name";
		}
	}
};

//�C�^�X�^�_HP3
class SK_Heal : public Skill {
public:
	// �غc�l
	SK_Heal(MonsterProperty& pp):Skill(pp){};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		pp.increaseAbility(HP, 3);
		// �s�y token
		this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		this->st = getEmptyToken();
	}
};

//�H�����[�������m�v�T���ˮ`1~3
class SK_Burning : public Skill {
public:
	// �غc�l
	SK_Burning(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ͦ� �����ƭ�
		int exDamege = (rand() % 3) + 1;
		
		// �ϥΧޯ��T��
		std::string point; // �M�w�O�_�n�νƼƫ��A�C
		point = exDamege > 1 ? " points" : " point";
		this->skillMsg = "Caused extra " + std::to_string(exDamege) + point + " damege.";
		
		// �s�y token
		this->st = SkillToken(this->skillName, this->skillMsg, YES_DECREASE, HP, exDamege);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		// �s�y token
		this->st = getEmptyToken();
	}
};

//���� 1/5 �Ҩ��ˮ`
class SK_Counter_Attack : public Skill {
public:
	// �غc�l
	SK_Counter_Attack(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �O�H�S�������A�A�����ӥ� �D�ʧޯ�A�ҥH �ޯ�W�r���ӴN�O ""�Ŧr��C
		this->st = getEmptyToken();
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		;
	}
};

//�K�̭��C��O�Ȫ��S���O
class SK_Immunology : public Skill {
public:
	// �غc�l
	SK_Immunology(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//�C�������l��2~3HP
class SK_Leech_Life : public Skill {
public:
	// �غc�l
	SK_Leech_Life(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//1 / 5���v�j�ק���
class SK_Avoid : public Skill {
public:
	// �غc�l
	SK_Avoid(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//1 / 5���v�⦸����
class SK_Double_Attack : public Skill {
public:
	// �غc�l
	SK_Double_Attack(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//�Q�������Ĥ褤�r�C�^�X - 2HP(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A����2�^�X)
class SK_Poison : public Skill {
public:
	// �غc�l
	SK_Poison(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//�����ɭ��C�Ĥ�t�׭�2(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A����2�^�X)
class SK_Lower_Speed : public Skill {
public:
	// �غc�l
	SK_Lower_Speed(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//�C�����쪺�ˮ` - 2
class SK_Rock_Skin : public Skill {
public:
	// �غc�l
	SK_Rock_Skin(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//�����ɭ��C�Ĥ訾�m�O2(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A����2�^�X)
class SK_Lower_Defence : public Skill {
public:
	// �غc�l
	SK_Lower_Defence(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

//�����ɭ��C�Ĥ�����O2(�@���u�o�ʤ@��, ���ͼv�T���U�@�^�X�}�l�p��A����2�^�X)
class SK_Lower_Attack : public Skill {
public:
	// �غc�l
	SK_Lower_Attack(MonsterProperty& pp) :Skill(pp) {};
	// �мg�����O
	virtual void use()override {
		// �ϥΧޯ��T��
		//this->skillMsg = "heal 3 hp.";
		// ����� �ƭ�
		//pp.increaseAbility(HP, 3);
		// �s�y token
		//this->st = SkillToken(this->skillName, this->skillMsg, NO, UNK, 0);
	}
	// �мg�����O �Q�����ɩ�Ĳ�o���ޯ�
	virtual void beAttacked()override {
		//this->st = getEmptyToken();
	}
};

