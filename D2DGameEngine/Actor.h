#pragma once
#include "IComponent.h"

enum EActorStatus
{
	AS_AWAKE, AS_INACTIVE, AS_ACTIVE, AS_DESTROY
};


class Actor : public IObject
{
protected:
	using ComponentRegistry = std::unordered_multimap<std::type_index, class IComponent*>;
	ComponentRegistry components;

	EActorStatus status = AS_AWAKE;
	class SceneComponent* rootComponent = nullptr;
	class World* world = nullptr;
public:
	Actor();
	virtual ~Actor();

	EActorStatus GetStatus() { return status; }

	void SetWorld(class World* _world) { world = _world; }
	class World* GetWorld() { return world; }

	/**
	 * @brief Actor�� ���¸� AS_ACTIVE�� �����մϴ�. 
	 */
	void Activate() { status = AS_ACTIVE; }

	/**
	 * @brief Actor�� ���¸� AS_INACTIVE�� �����մϴ�. 
	 */
	void Inactivate() { status = AS_INACTIVE; }

	void SetLocation(const float x, const float y);
	Math::Vector2 GetLocation() const;
	void SetRotation(const float _degree);
	void SetScale(const float x, const float y);
	D2D_TMat3x2F GetTrasnform() const;

	/**
	 * @brief Ư�� Ÿ���� ������Ʈ�� �����ɴϴ�.
	 * @tparam T ������Ʈ Ÿ��
	 * @return ������Ʈ ������. ã�� �� ������ nullptr
	 */
	template <typename T>
	T* GetComponent() {
		auto it = components.find(std::type_index(typeid(T)));
		return (it == components.end()) ? nullptr : (T*)it->second;
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

