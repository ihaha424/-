#pragma once

#include "ShapeComponent.h"

class BoxComponent : public ShapeComponent {
protected:
	Extent2D boxExtent{};

public:

	Extent2D GetScaledCapsuleHalfHeight() const {
		DXVec3 p{ boxExtent.width, boxExtent.height, 0.f };
		p = DXVec3::Transform(p, S);
		return { p.x, p.y };
	}

	Extent2D GetBoxExtent() const {
		return { boxExtent.width, boxExtent.height };
	}

	void InitBoxExtent(const Extent2D& _boxExtent) {
		boxExtent = _boxExtent;
	}

	/**
	 * @brief �ڽ� ����� �ٲߴϴ�.
	 * @param _boxExtent 
	 */
	void SetBoxExtent(const Extent2D& _boxExtent) {
		boxExtent = _boxExtent;
		// TODO: �ݸ��� üũ
	}

	virtual BoxCircleBounds CalculateLocalBounds() const override {
		// TODO: ���� Ʈ������ ����
		return BoxCircleBounds(Box::BuildAABB({ 0, 0 }, boxExtent));
	}

	virtual bool GetCollisionShape(float inflation, CollisionShape& collisionShape) const {
		Extent2D scaledExtent = GetScaledCapsuleHalfHeight();
		collisionShape.SetBox({ scaledExtent.width * inflation, scaledExtent.height * inflation });
		return true;
	}

	virtual bool IsZeroExtent() const {
		CollisionShape collisionShape;
		collisionShape.SetBox({ boxExtent.width, boxExtent.height });
		return collisionShape.IsNearlyZero();
	}

protected:
	bool CheckComponentOverlapComponentImpl(
		PrimitiveComponent* primComp,
		const DXVec2& pos,
		const DXMat4x4& rotation) override;
	bool CheckComponentOverlapComponentWithResultImpl(
		PrimitiveComponent* primComp,
		const DXVec2& pos, const DXMat4x4& rotation,
		std::vector<OverlapResult>& outOverlap) override;
};
