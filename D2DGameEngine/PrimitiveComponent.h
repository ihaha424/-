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
	PrimitiveComponent(Actor* _owner);
	~PrimitiveComponent();

	DXVec2 GetCenterOfMass() const {
		return GetComponentLocation();
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

	virtual BoxCircleBounds CalculateBounds(const Math::Matrix& _worldTransform) const override {
		DXVec2 c { bounds.center.x, bounds.center.y };
		c = DXVec2::Transform(c, _worldTransform);

		DXVec2 e { bounds.boxExtent.width, bounds.boxExtent.height };
		e = DXVec2::Transform(e, _worldTransform);
		
		return BoxCircleBounds(Box{ c, e });
	}

	virtual BoxCircleBounds CalculateLocalBounds() const {
		return BoxCircleBounds{};
	}

	virtual void UpdateBounds() override {
		bounds = CalculateLocalBounds();
	}

	/**
	 * @brief �ݸ��� ������ �����մϴ�. �ݸ��� ������ ������Ʈ�� ������ ���� �ݿ��ؾ� �մϴ�.
	 * @param Inflation 
	 * @param CollisionShape 
	 * @return 
	 */
	virtual bool GetCollisionShape(float Inflation, CollisionShape& CollisionShape) const {
		return false;
	}

	virtual bool IsZeroExtent() const {
		return true;
	}

	/**
	 * @brief �ٸ� ������Ʈ�� Ư�� ��ġ���� ������Ʈ�� ��ġ���� Ȯ���մϴ�.
	 * @param component ������ �׽�Ʈ�� ������Ʈ
	 * @param pos �ٸ� ������Ʈ�� �׽�Ʈ�� ��ġ
	 * @param rotation �ٸ� ������Ʈ�� �����̼� ��Ʈ����
	 * @return True �̸� ������ �մϴ�.
	 */
	bool CheckComponentOverlapComponent(PrimitiveComponent* component, const DXVec2& pos, const DXMat4x4& rotation) {
		return CheckComponentOverlapComponentImpl(component, pos, rotation);
	}

	bool CheckComponentOverlapComponentWithResult(
		PrimitiveComponent* component, const DXVec2& pos, const DXMat4x4& rotation,
		std::vector<OverlapResult>& outOverlap) {
		return CheckComponentOverlapComponentWithResultImpl(component, pos, rotation, outOverlap);
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
			// Clamp acceleration
			DXVec2 accDir = acceleration; accDir.Normalize();
			acceleration.Clamp(accDir * minAcceleration, accDir * maxAccelaration);
			// Update velocity
			velocity += acceleration * _dt;
			acceleration = { 0, 0 }; // Reset acceleration each frame

			// Clamp velocities
			float speed = velocity.Length();
			DXVec2 unitVel = velocity; unitVel.Normalize();
			speed = Clamp(speed, minSpeed, maxSpeed);
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
		const DXVec2& pos, 
		const DXMat4x4& rotation);

	virtual bool CheckComponentOverlapComponentWithResultImpl(
		PrimitiveComponent* component, 
		const DXVec2& pos, const DXMat4x4& rotation,
		std::vector<OverlapResult>& outOverlap);

	virtual bool MoveComponentImpl(
		const DXVec2& delta,
		bool bSweep,
		HitResult* outHitResult) override {
		// TODO:
		Super::MoveComponentImpl(delta, bSweep, outHitResult);
		return true;
	}

};

// TODO: Line trace, sphere trace, sphere overlap