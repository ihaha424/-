#pragma once
#include "../D2DGameEngine/IComponent.h"

enum ESkillType
{
	ST_PROJECTILE, ST_RANGE, ST_BUFF, ST_SPECIAL
};

enum ESkillElement
{
	SE_FIRE, SE_WATER, SE_LIGHT, SE_DARKNESS
};


class Skill : public IComponent
{
	static int wholeSkillLevel;

protected:
	class TestPlayerController* controller;
	class Player* player;
	std::wstring id;
	ESkillType type;
	int level = 0;
	int count = 0;
	int mana = 0;
	
public:
	Skill();
	virtual ~Skill();

	static int GetWholeSkillLevel() { return wholeSkillLevel; }

	void SetPlayer(TestPlayerController* _pc);

	/**
	 * @brief ��ų�� ����մϴ�. ��ų ��� ī��Ʈ�� �����մϴ�. 
	 */
	virtual void UseSkill();


	virtual void Update(float _dt) override;

};

