#pragma once

#include "framework.h"

struct DamageType {
	bool bCausedByWorld : 1; // ���� ������, ȯ�湰�� ���� ������ ��.
	float damageFalloff; // �Ÿ��� ���� ������ ������ 1.0 = ����, 2.0 = �Ÿ��� ����
	float damageImpulse; // �������� ���Ϳ� ������ ��ݷ�

	static DamageType Default() {
		return { false, 1.0, 0.0 };
	}
};


//struct DamageType_Fire : public DamageType {
//
//};


// Actor TakeDamage;
