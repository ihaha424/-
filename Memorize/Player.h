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
	const int maxLevel = 50;
	int level = 1;
	int exp = 0;
	Stat stat;
public:
	Player(class World* _world);
	virtual ~Player();

	void LevelUp();

};

