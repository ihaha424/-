#pragma once
#include "../D2DGameEngine/Character.h"


struct Stat
{
	float maxHp; //HP
	float maxMp; //MP
	float hpRegenPerSecond; //�ʴ� HP ȸ����
	float mpRegenPerSecond; //�ʴ� MP ȸ����
	float skillRange; //���� ����
	int castingSpeed; //ĳ���� �ӵ�
	int numProjectiles; //����ü ����
	int defaultDamage; //�⺻ �����
};

class Player : public Character
{
	int level = 1;
	Stat stat;
public:
	Player(class World* _world);
	virtual ~Player();

};

