#pragma once

#include "framework.h"

class PrimitiveComponent;
struct HitResult {
	bool bBlockingHit : 1;	// ���ŷ �浹�� ������� ǥ��
	bool bStartPenetrating : 1; // �浹�� ��� ���� �Ǿ�����
	PrimitiveComponent* hitComponent;	// �浹 ���� ������Ʈ

	float distance;		// Ʈ���̽� ���������� �����̼Ǳ����� �Ÿ�
	DXVec2 impactNormal;	// �浹���� ������Ʈ�� ��Ʈ ���������� �븻 ����
	DXVec2 impactPoint;		// Ʈ���̽� ������ ��Ʈ ����

	DXVec2 location;	// ������ ������Ʈ�� �浹�� ��ġ

	DXVec2 normal;	// �浹���� ������Ʈ�� �߽������� ������ ������Ʈ �߽��������� ����
	float penetrationDepth;	// ���� ������ ����� ���͸� ���� �� �ִ� ���, �븻 ���͸� ���� �浹���� ����� ���� �Ÿ�.

	float time; // (0.0 ���� 1.0) �浹�� ���� ��� Ʈ���̽� �������� Ʈ���̽� ������ ������ ��
	DXVec2 traceStart;	// Ʈ���̽��� ������
	DXVec2 traceEnd;		// Ʈ���̽��� ���� �� ������

	class Actor* GetActor();

	PrimitiveComponent* GetComponent() {
		return hitComponent;
	}
};
