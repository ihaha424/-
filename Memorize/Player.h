#pragma once
#include "../D2DGameEngine/Character.h"
#include "../D2DGameEngine/Reflection.h"


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

class Player : public Character, IReflection
{
	const int maxLevel = 50;
	int level = 1;
	int exp = 0;
	float moveSpeed = 100;
	int	ReflectionData = 100;
	int	ReflectionData1 = 100;
	int	ReflectionData2 = 100;
	std::vector<float> ReflectionData3 = {};
	Stat stat;
public:
	Player(class World* _world);
	virtual ~Player();

	void LevelUp();


	// IReflection��(��) ���� ��ӵ�
	void ReflectionIn() override;
	void ReflectionOut() override;

};

