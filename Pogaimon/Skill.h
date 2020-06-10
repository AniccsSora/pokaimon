#pragma once
// --------------------------------------------- < class Prototype>
class Skill;
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
// --------------------------------------------- </class Prototype>
class Skill {};
class Heal : public Skill {};
class Burning : public Skill {};
class Counter_Attack : public Skill {};
class Immunology : public Skill {};
class Leech_Life : public Skill {};
class Avoid : public Skill {};
class Double_Attack : public Skill {};
class Poison : public Skill {};
class Lower_Speed : public Skill {};
class Rock_Skin : public Skill {};
class Lower_Defence : public Skill {};
class Lower_Attack : public Skill {};

