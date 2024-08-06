#pragma once

#include "Event.h"

#include "DamageType.h"

#include "HitResult.h"

struct DamageEvent : public Event<DamageEvent> {
	DamageType damageType;
};

/**
 * @brief ����Ʈ ������ �̺�Ʈ
 */
struct PointDamageEvent : public DamageEvent {
	float damage;					// ������ ��
	HitResult hitInfo;		// �������� ���� ��ġ�� ����
	DXVec2 shotDirection;	// ���� ����� ����
};

/**
 * @brief ���� ������ ����
 */
struct RadialDamageInfo {
	float maxDamage;		// �ִ� ������
	float minDamage;		// �ּ� ������
	float damageFalloff;// �Ÿ��� ���� ������ ������. 1.0 = ����, 2.0 = �Ÿ��� ����
	float innerRadius;	// �ƽ� ������ ���ϴ� ������
	float outerRadius;	// �������� ������ �ʴ� ���� �ٱ����� ������
	
	float GetDamageScale(float _distanceFromCenter) {
		if (_distanceFromCenter <= innerRadius) {
			return MaxDamage;
		}
		else if (_distanceFromCenter < outerRadius) {
			float ratio = 1.f - (_distanceFromCenter - innerRadius) / (outerRadius - innerRadius);
			float falloff_ratio = std::powf(ratio, damageFalloff);
			return minDamage + (maxDamage - minDamage) * falloff_ratio;
		}
		else {
			return 0.f;
		}
	}

	float GetMaxRadius() {
		return outerRadius;
	}
};

/**
 * @brief ���� ���� �̺�Ʈ
 */
struct RadialDamageEvent : public DamageEvent {
	std::vector<HitResult> componentHits;	// �������� ���� ��ġ�� ����
	DXVec2 origin;	// ���� ������ ����
	RadialDamageInfo radialDamageInfo;
};
