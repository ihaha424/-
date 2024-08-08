#pragma once

#include "SceneComponent.h"

#include "Actor.h"

#include "CollisionShape.h"
#include "CollisionProperty.h"

#include "HitResult.h"
#include "OverlapResult.h"
#include "OverlapInfo.h"

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
	using OverlappingComponentSet = std::map<PrimitiveComponent*, OverlapInfo>;
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
		/*if (bApplyImpulseOnDamage)
		{
			UDamageType const* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
			if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
			{
				FPointDamageEvent* const PointDamageEvent = (FPointDamageEvent*)&DamageEvent;
				if ((DamageTypeCDO->DamageImpulse > 0.f) && !PointDamageEvent->ShotDirection.IsNearlyZero())
				{
					if (IsSimulatingPhysics(PointDamageEvent->HitInfo.BoneName))
					{
						FVector const ImpulseToApply = PointDamageEvent->ShotDirection.GetSafeNormal() * DamageTypeCDO->DamageImpulse;
						AddImpulseAtLocation(ImpulseToApply, PointDamageEvent->HitInfo.ImpactPoint, PointDamageEvent->HitInfo.BoneName);
					}
				}
			}
			else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
			{
				FRadialDamageEvent* const RadialDamageEvent = (FRadialDamageEvent*)&DamageEvent;
				if (DamageTypeCDO->DamageImpulse > 0.f)
				{
					AddRadialImpulse(RadialDamageEvent->Origin, RadialDamageEvent->Params.OuterRadius, DamageTypeCDO->DamageImpulse, RIF_Linear, DamageTypeCDO->bRadialDamageVelChange);
				}
			}
		}*/
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

	bool IsRegisterd() {
		// GetWorld()->CheckRegistration();
		return false;
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

	virtual bool CheckSweepComponent(
		HitResult& outHit,
		const DXVec2& start,
		const DXVec2& end,
		const DXMat4x4& rotation,
		const CollisionShape& collisionShape,
		const ECollisionChannel collisionChannel,
		const CollisionProperty& collisionProperty);

	void DispatchBlockingHit(Actor& owner, HitResult& blockingHit) {
		PrimitiveComponent* blockingHitComponent = blockingHit.hitComponent;
		if (blockingHitComponent) {
			//owner.DispatchBlockingHit(this, blockingHitComponent, true, blockingHit);

			Actor* blockingHitActor = blockingHitComponent->GetOwner();
			if (blockingHitActor) {
				//blockingHitActor->(blockingHitComponent, this, false, blockingHit);
			}
		}
	}

	bool IsOverlappingComponent(const PrimitiveComponent* otherComp) const {
		// TODO:
	}

	/**
	 * @brief Begin tracking an overlap interaction with the component specified.
	 * @param otherOverlap 
	 * @param bDoNotifies 
	 */
	void BeginComponentOverlap(const OverlapInfo& otherOverlap, bool bDoNotifies);

	/**
	 * @brief End tracking an overlap interaction
	 * @param otherOverlap 
	 * @param bDoNotifies 
	 * @param bSkipNotifySelf 
	 */
	void EndComponentOverlap(const OverlapInfo& otherOverlap, bool bDoNotifies, bool bSkipNotifySelf=false);

	// TODO: Place it in the UpdateOverlaps()
	void PushOverlappingComponent(PrimitiveComponent* otherComponent, const OverlapInfo& overlapInfo) {
		currentlyOverlappingComponents.insert({ otherComponent, overlapInfo });
	}

	void PopOverlappingComponent(PrimitiveComponent* otherComponent) {
		currentlyOverlappingComponents.erase(otherComponent);
	}

	/**
	 * @brief ������ ������Ʈ�� ������Ʈ �մϴ�.
	 */
	virtual void UpdateOverlaps(const std::vector<OverlapInfo>& overlaps, bool bDoNotifies = true);

	bool IsSimulatingPhysics() override {
		return bSimulatePhysics;
	}

	virtual DXVec2 GetComponentVelocity() const override {
		return Super::GetComponentVelocity();
	}

	// Bounds

	virtual BoxCircleBounds CalculateBounds(const Math::Matrix& _worldTransform) const override {
		DXVec2 c{ bounds.center.x, bounds.center.y };
		c = DXVec2::Transform(c, _worldTransform);

		DXVec2 e{ bounds.boxExtent.width, bounds.boxExtent.height };
		e = DXVec2::Transform(e, _worldTransform);

		return BoxCircleBounds(Box{ c, e });
	}

	virtual BoxCircleBounds CalculateLocalBounds() const {
		return BoxCircleBounds{};
	}

	virtual void UpdateBounds() override {
		bounds = CalculateLocalBounds();
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

	static void PullBackHit(HitResult& Hit, const DXVec2& Start, const DXVec2& End, const float Dist)
	{
		const float DesiredTimeBack = Clamp(0.1f, 0.1f / Dist, 1.f / Dist) + 0.001f;
		Hit.time = Clamp(Hit.time - DesiredTimeBack, 0.f, 1.f);
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
		HitResult* outHitResult) override;

};

// TODO: Line trace, sphere trace, sphere overlap