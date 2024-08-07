#include "Skill.h"
#include "Player.h"

int Skill::wholeSkillLevel = 0;

Skill::Skill(World* _world, ESkillType _type, std::wstring _id) : Actor(_world)
{
	type = _type;
	id = _id;
}

Skill::~Skill()
{
}

void Skill::UseSkill()
{
	count++;

	//TODO
	//�÷��̾� ���� ���

}

void Skill::Update(float _dt)
{
	//5ȸ ��� �� ���� ������ �ȴ�.
	if (count >= 5)
	{
		count = 0;
		level++;
		wholeSkillLevel++;
	}
}
