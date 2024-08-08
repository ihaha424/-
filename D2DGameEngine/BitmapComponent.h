#pragma once

#include "PrimitiveComponent.h"
#include "SpriteResource.h"
#include "ResourceManager.h"

// NOTE: ���࿡ ��Ʈ�� ������Ʈ���� �ݸ��� üũ�ϰ� ������.
// bCanCollide = true
// CollisionProperty ����
// bool GetCollisionShape(float, CollisionShape&) const �����ε��ؼ� �ݸ��� ���� ����

class BitmapComponent : public PrimitiveComponent {
	using Super = SceneComponent;

	D2D_RectF frame;
	std::shared_ptr<SpriteResource> sprite;

	Math::Matrix imageTransform;

public:

	BitmapComponent() : 
		frame{ 0.f, 0.f, 0.f, 0.f },
		sprite{ nullptr },
		imageTransform{ Math::Matrix::Identity } {
		SetTickProperties(TICK_RENDER);
	}

	virtual ~BitmapComponent() {
		// TODO: ��������Ʈ ������
	}

	void SetSprite(const wchar_t* path) {
		sprite = ResourceManager::LoadResource<SpriteResource>(path);
		if (!sprite->GetResource()) {
			throw std::exception("BitmapScene: image asset is not found!");
		}
		// Fit the frame with the image width and height
		frame = {
			0,0,
			GetSpriteWidth(),
			GetSpriteHeight()
		};

	}

	std::shared_ptr<SpriteResource> GetSprite() { return sprite; }

	float GetSpriteWidth() const {
		return sprite->GetResource()->GetSize().width;
	}

	float GetSpriteHeight() const {
		return sprite->GetResource()->GetSize().height;
	}

	float GetFrameWidth() const {
		return frame.right - frame.left;
	}

	float GetFrameHeight() const {
		return frame.top - frame.bottom;
	}

	void SetFrame(const D2D_Point2F& ul, const D2D_Point2F& lr) {
		frame = { ul.x, ul.y, lr.x, lr.y };
	}

	void FlipX(bool flip) {
		imageTransform._11 = flip ? -1.f : 1.f;
	}

	void FlipY(bool flip) {
		imageTransform._22 = flip ? -1.f : 1.f;
	}

	virtual D2D_RectF GetCurrFrame() { return frame; }
	virtual Math::Matrix GetWorldTransform() const override;
	virtual void Render(class D2DRenderer* _renderer);
};

