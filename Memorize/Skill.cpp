#include "Skill.h"
#include "Player.h"
#include "GPlayerController.h"

int Skill::wholeSkillLevel = 0;

Skill::Skill()
{
}

Skill::~Skill()
{
}

void Skill::SetPlayer(GPlayerController* _pc)
{
	controller = _pc;
	player = controller->GetPlayer();
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
