#pragma once
#include "../D2DGameEngine/Character.h"
#include "../D2DGameEngine/Reflection.h"


struct Stat
{
	float hp;
	float maxHp; //HP
	float mp;
	float maxMp; //MP
	float hpRegenPerSecond; //�ʴ� HP ȸ����
	float mpRegenPerSecond; //�ʴ� MP ȸ����
	float skillRange; //���� ����
	int castingSpeed; //ĳ���� �ӵ�
	int numProjectiles; //����ü ����
	int defaultDamage; //�⺻ �����
	int defaultAttackSpeed; //�⺻ ���� �ӵ�

	Stat operator+(Stat stat)
	{
		hp += stat.hp;
		maxHp += stat.maxHp;
		mp += stat.mp;
		maxMp += stat.maxMp;
		hpRegenPerSecond += stat.hpRegenPerSecond;
		mpRegenPerSecond += stat.mpRegenPerSecond;
		skillRange += stat.skillRange;
		castingSpeed += stat.castingSpeed;
		numProjectiles += stat.numProjectiles;
		defaultDamage += stat.defaultDamage;
		defaultAttackSpeed += stat.defaultAttackSpeed;
	}
	Stat operator-()
	{
		hp *= -1;
		maxHp *= -1;
		mp *= -1;
		maxMp *= -1;
		hpRegenPerSecond *= -1;
		mpRegenPerSecond *= -1;
		skillRange *= -1;
		castingSpeed *= -1;
		numProjectiles *= -1;
		defaultDamage *= -1;
		defaultAttackSpeed *= -1;
	}
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
	void AddToStat(Stat _addStat);

	// IReflection��(��) ���� ��ӵ�
	void ReflectionIn() override;
	void ReflectionOut() override;

};

