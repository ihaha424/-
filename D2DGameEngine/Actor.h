#pragma once
#include "IObject.h"

enum EActorStatus
{
	AS_AWAKE, AS_INACTIVE, AS_ACTIVE, AS_DESTROY
};


class Actor : public IObject
{
private:
	std::vector<class IComponent*> components;
	EActorStatus status = AS_AWAKE;

protected:
	class IComponent* rootComponent = nullptr;

public:
	Actor();
	virtual ~Actor();

	/**
	 * @brief Actor�� ���¸� AS_ACTIVE�� �����մϴ�. 
	 */
	void Activate() { status = AS_ACTIVE; }

	/**
	 * @brief Actor�� ���¸� AS_INACTIVE�� �����մϴ�. 
	 */
	void Inactivate() { status = AS_INACTIVE; }

	//void SetLocation(const Math::Vector2 _location) { rootComponent->SetWorldLocation(_location); }
	//Math::Vector2 GetLocation() const { return rootComponent->GetWorldLocation(); }
	//void SetRotation(const Math::Vector2 _rotation) { rootComponent->SetWorldRotation(_rotation); }
	//Math::Vector2 GetRotation() const { return rootComponent->GetWorldRotation(); }
	//void SetScale(const float _scale) { rootComponent->SetWorldScale(_scale); }
	//Math::Vector2 GetScale() const { return rootComponent->GetWorldScale(); }
	//void SetTransform(const D2D_TMat3x2F _transform) { rootComponent->SetWorldTransform(_transform); }
	//D2D_TMat3x2F GetTrasnform() const { return rootComponent->GetWorldTransform(); }

	/**
	 * @brief Ư�� Ÿ���� ������Ʈ�� �����ɴϴ�.
	 * @tparam T ������Ʈ Ÿ��
	 * @return ������Ʈ ������. ã�� �� ������ nullptr
	 */
	template <typename T>
	T* GetComponent()
	{
		for (auto component : components)
		{
			T* t = dynamic_cast<T*>(component);
			if (t != nullptr)
				return t;
		}
		return nullptr;
	}

	/**
	 * @brief Actor�� ���¸� AS_AWAKE���� AS_ACTIVE�� �����մϴ�.
	 *		  ������ ���۵� �� ȣ��˴ϴ�. 
	 */
	virtual void BeginPlay() { status = AS_ACTIVE; };

	/**
	 * @brief Actor�� ���¸� AS_DESTROY�� �����մϴ�. 
	 */
	virtual bool Destroy();

	virtual void FixedUpdate(float _fixedRate) override;
	virtual void PreUpdate(float _dt) override;
	virtual void Update(float _dt) override;
	virtual void PostUpdate(float _dt) override;
	virtual void Render(class D2DRenderer* _renderer) override;

};

