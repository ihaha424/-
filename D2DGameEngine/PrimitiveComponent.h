#pragma once

#include "SceneComponent.h"

#include "CollisionShape.h"
#include "CollisionProperty.h"

#include "HitResult.h"
#include "OverlapResult.h"

/**
 * @brief geometry to be rendered or used as collision.
 */
class PrimitiveComponent : public SceneComponent {
	using Super = SceneComponent;

public:
	bool isVisible{ true };
	
	bool bSimulatePhysics{ false };
	bool bApplyImpulseOnDamage{ false };

	// Physics
	float mass{ 1.0f };
	float frictionCoefficient{ 0.9f };
	float	dragForce{ 0.f };
	float minAcceleration{ 0.f };
	float maxAccelaration{ 10000.f };
	float minSpeed{ 0.f };
	float maxSpeed{ 1000.f };
	DXVec2 acceleration{};

	// Collision
	bool bCanCollide{ false };
	bool bGenerateHitEvent{ false };
	bool bGenerateOverlapEvent{ false };
	CollisionProperty collisionProperty;	// Default NoCollision
	using OverlappingComponentSet = std::map<PrimitiveComponent*, HitResult>;
	OverlappingComponentSet previouslyOverlappingComponents;
	OverlappingComponentSet currentlyOverlappingComponents;

	// Damage
	bool bTakeDamage{ false };

public:
	PrimitiveComponent();
	~PrimitiveComponent();

	DXVec2 GetCenterOfMass() const {
		D2D_Point2F loc = GetComponentLocation();
		return { loc.x, loc.y };
	}

	virtual float GetMass() const { return mass; }

	// Physics System

	/**
	 * @brief ���� ���մϴ�. 
	 * @param force ���� ������ ����
	 * @param bPhysicalForce True �̸� ���ӵ��� ��ȭ���� ������ ����˴ϴ�.
	 */
	virtual void AddForce(DXVec2 force, bool bPhysicalForce) {
		if (bPhysicalForce && bSimulatePhysics) {
			acceleration += force / mass;
		}
		else {
			acceleration += force;
		}
	}

	/**
	 * @brief ��ݷ��� ���մϴ�.
	 * @param impuslse ��ݷ��� ������ ����
	 * @param bPhysicalImpulse True �̸� �ӵ��� ��ȭ�� ������ ����˴ϴ�.
	 */
	virtual void AddImpulse(DXVec2 impulse, bool bPhysicalImpulse) {
		if (bPhysicalImpulse) {
			velocity += impulse / mass;
		}
		else {
			velocity += impulse;
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

	void SetCollisionEnabled(CollisionEnabled::Type type) {
		collisionProperty.collisionEnabled = type;
		if (type == CollisionEnabled::NoCollision) {
			bCanCollide = false;
			// Unregister collision
		}
		else {
			bCanCollide = true;
			// Register collision
		}
	}

	void SetCollisionObjectType(ECollisionChannel objectType) {
		collisionProperty.objectType = objectType;
	}

	void SetCollisionResponseToChannels(CollisionResponseContainer responseContainer) {
		collisionProperty.responseContainer = responseContainer;
	}

	// Collision
	virtual bool IsCollisionEnabled() const {
		return collisionProperty.collisionEnabled == CollisionEnabled::EnableCollision;
	}

	virtual CollisionEnabled::Type GetCollisionEnabled() const override {
		return CollisionEnabled::NoCollision;
	}

	virtual ECollisionChannel GetCollisionObjectType() const override {
		return ECollisionChannel::WorldStatic;
	}

	virtual BoxCircleBounds CalculateBounds(const D2D_Mat3x2F& _worldTransform) const override {
		D2D_Point2F c = { bounds.center.x, bounds.center.y };
		c = c * _worldTransform;

		D2D_Point2F e = { bounds.boxExtent.width, bounds.boxExtent.height };
		e = e * _worldTransform;
		
		return BoxCircleBounds(Box{ {c.x, c.y}, {e.x, e.y} });
	}

	virtual BoxCircleBounds CalculateLocalBounds() const {
		return BoxCircleBounds{};
	}

	virtual void UpdateBounds() override {
		bounds = CalculateLocalBounds();
	}

	virtual bool GetCollisionShape(float Inflation, CollisionShape& CollisionShape) const {
		return false;
	}

	virtual bool IsZeroExtent() const {
		return true;
	}

	/**
	 * @brief ������Ʈ�� Ư�� ��ġ���� �ٸ� ������Ʈ�� ��ġ���� Ȯ���մϴ�.
	 * @param component ������ �׽�Ʈ�� ������Ʈ
	 * @param pos �� ������Ʈ�� �׽�Ʈ�� ��ġ
	 * @return True �̸� ������ �մϴ�.
	 */
	bool CheckComponentOverlapComponent(PrimitiveComponent* component, const DXVec2& pos) {
		return CheckComponentOverlapComponentImpl(component, pos);
	}

	bool CheckComponentOverlapComponentWithResult(
		PrimitiveComponent* component, const DXVec2& pos,
		std::vector<OverlapResult>& outOverlap) {
		return CheckComponentOverlapComponentWithResultImpl(component, pos, outOverlap);
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

	bool IsOverlappingComponent(const PrimitiveComponent* otherComp) const {
		// TODO:
	}

	// TODO: Place it in the UpdateOverlaps()
	void PushOverlappingComponent(PrimitiveComponent* otherComponent, const HitResult& hitResult) {
		currentlyOverlappingComponents.insert({ otherComponent, hitResult });
	}

	/**
	 * @brief ������ ������Ʈ�� ������Ʈ �մϴ�.
	 */
	virtual void UpdateOverlaps() override;

	bool IsSimulatingPhysics() override {
		return bSimulatePhysics;
	}

	virtual DXVec2 GetComponentVelocity() const override {
		return Super::GetComponentVelocity();
	}

	// Physics update
	virtual void FixedUpdate(float _dt) override {
		if (bSimulatePhysics) {
			// Simple semi-implicit Euler integration
			acceleration -= velocity * dragForce; // Damping effect
			velocity += acceleration * _dt;
			acceleration = { 0, 0 }; // Reset acceleration each frame

			// Clamp velocities
			float speed = velocity.Length();
			DXVec2 unitVel = velocity;
			unitVel.Normalize();
			speed = speed < minSpeed ? minSpeed : maxSpeed < speed ? maxSpeed : speed;
			velocity = unitVel * speed;

			// Apply the movement
			HitResult hitResult;
			MoveComponent(velocity * _dt, true, &hitResult);
		}
		else {
			Super::FixedUpdate(_dt);
		}
	}

protected:

	virtual bool CheckComponentOverlapComponentImpl(
		PrimitiveComponent* primComp,
		const DXVec2& pos);

	virtual bool CheckComponentOverlapComponentWithResultImpl(
		PrimitiveComponent* component, const DXVec2& pos,
		std::vector<OverlapResult>& outOverlap);

	virtual bool MoveComponentImpl(
		const DXVec2& delta,
		bool bSweep,
		HitResult* outHitResult) override {
		// TODO:
		return false;
	}

};

// TODO: Line trace, sphere trace, sphere overlap