#pragma once

#include "SceneComponent.h"

#include "CollisionShape.h"

#include "HitResult.h"

class PrimitiveComponent : public SceneComponent {
	using Super = SceneComponent;

	bool isVisible{ true };
	bool isCollision{ false };
	bool isPhysicsCollision{ false };
	bool bApplyImpulseOnDamage{ false };

	// Physics
	float mass{ 1.0f };
	float frictionCoefficient{ 0.9f };
	float	dragForce{ 0.f };
	float minAcceleration{ 0.f };
	float maxAccelaration{ 10000.f };
	float minSpeed{ 0.f };
	float maxSpeed{ 1000.f };
	DXVec2 accelaration{};

	// Collision
	using OverlappingComponentSet = std::map<PrimitiveComponent*, HitResult>;
	OverlappingComponentSet previouslyOverlappingComponents;
	OverlappingComponentSet currentlyOverlappingComponents;

	// Health
	bool bTakeDamage{ false };
	float health;

public:
	PrimitiveComponent();
	~PrimitiveComponent();

	DXVec2 GetCenterOfMass() const {
		// TODO:
	}

	virtual float GetMass() const { return mass; }

	virtual CollisionShape GetCollisionShape() const {
		// TODO:
		return CollisionShape();
	}

	/**
	 * @brief ������Ʈ�� Ư�� ��ġ���� �ٸ� ������Ʈ�� ��ġ���� Ȯ���մϴ�.
	 * @param component ������ �׽�Ʈ�� ������Ʈ
	 * @param pos �� ������Ʈ�� ��ġ
	 * @return ��ġ��
	 */
	bool CheckComponentOverlapComponent(
		PrimitiveComponent* component,
		const DXVec2 pos) {
		// TODO:
	}

	virtual bool CheckLineTraceComponent(
		HitResult& outHit,
		const DXVec2 start,
		const DXVec2 end) {
		// TODO:
		return true;
	}

	void DispatchBlockingHit() {
		// TODO:
	}

	// Physics System

	/**
	 * @brief ���� ���մϴ�. 
	 * @param force ���� ������ ����
	 * @param bPhysicalForce True �̸� ���ӵ��� ��ȭ���� ������ ����˴ϴ�.
	 */
	virtual void AddForce(DXVec2 force, bool bPhysicalForce) {
		if (bPhysicalForce) {
			// TODO:
		}
		else {
			// TODO:
		}
	}

	/**
	 * @brief ��ݷ��� ���մϴ�.
	 * @param impuslse ��ݷ��� ������ ����
	 * @param bPhysicalImpulse True �̸� �ӵ��� ��ȭ�� ������ ����˴ϴ�.
	 */
	virtual void AddImpulse(DXVec2 impuslse, bool bPhysicalImpulse) {
		if (bPhysicalImpulse) {
			// TODO:
		}
		else {
			// TODO:
		}
	}


	// Damage System

	/**
	 * @brief 
	 * @param _damageAmount 
	 * @param damageEvent 
	 * @param instigator 
	 * @param damageCauser 
	 */
	virtual void ReceiveComponentDamage(
		float _damageAmount,
		const struct DamageType& damageEvent,
		class Controller* instigator,	// �������� �� Player Controller �ƴϸ� AIController
		class Actor* damageCauser	// �������� �� ������Ʈ. ����, �Ѿ�, ����ź ��.
	) {
		// TODO:
	}

	// Collision Callbacks
	// TODO: Cursor Events
	virtual void OnBeginCursorOver() {}
	virtual void OnEndCursorOver() {}
	virtual void OnClicked() {}
	// Collision
	virtual void OnComponentBeginOverlap() {}
	virtual void OnComponentEndOverlap() {}
	virtual void OnComponentHit() {}

	// Tick
	virtual void FixedUpdate(float _dt) override {
		Super::Update(_dt);
	}

protected:

	virtual bool MoveComponentImpl(
		const D2D_Vec2F& delta,
		bool bSweep,
		HitResult& outHitResult) {
		// TODO:
		return false;
	}

};

// TODO: Line trace, sphere trace, sphere overlap