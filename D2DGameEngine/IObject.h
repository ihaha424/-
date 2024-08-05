#pragma once

#include "framework.h"

typedef enum TickPropertyBit {
	TICK_NONE = 0U,
	TICK_PHYSICS = (1U << 1),
	TICK_PRE_UPDATE = (1U << 2),
	TICK_UPDATE = (1U << 3),
	TICK_POST_UPDATE = (1U << 4),
	TICK_RENDER = (1U << 5),
} TickPropertyBit;
using TickPropertyFlags = Flags;

class IObject {
	bool tickEveryFrame{ true };
	float tickInterval{ 0.0 };
	TickPropertyFlags tickPropertyFlags{ TICK_NONE };

public:

	/**
	 * @brief ���ο� ������Ʈ(���� �Ǵ� ������Ʈ)�� �����Ͽ� ��ȯ�մϴ�.
	 * @tparam T: IObject�� ��ӹ��� Ŭ����
	 * @return 
	 */
	template <typename T>
	T* CreateDefaultSubobject() const
	{
		static_assert(std::is_base_of<IObject, T>::value, "T must inherit from IObject");

		T* newObject = new T;
		return newObject;
	}

	/**
	 * @brief �� �����Ӹ��� ������Ʈ �ؾ������� ǥ���մϴ�.
	 * @param _tickEverySecond True - �� �����Ӹ��� ������Ʈ �մϴ�.
	 */
	void EnableTickEverySecond(bool _tickEverySecond) {
		tickEveryFrame = _tickEverySecond;
	}
	/**
	 * @brief �� �����Ӹ��� ������Ʈ �ؾ��ϴ��� ���θ� ��ȯ�մϴ�.
	 * @return True - �� �����Ӹ��� ������Ʈ �մϴ�.
	 */
	bool IsTickingEverySecond() {
		return tickEveryFrame;
	}
	/**
	 * @brief ������Ʈ ���͹��� �����մϴ�.
	 * @param _tickInterval 0.0 �� ��� �� ������ ������Ʈ
	 */
	void SetTickInterval(float _tickInterval) {
		tickInterval = _tickInterval;
	}
	/**
	 * @brief ������Ʈ ���͹��� ��ȯ�մϴ�.
	 * @return float: ������Ʈ ���͹�
	 */
	float GetTickInterval() {
		return tickInterval;
	}
	/**
	 * @brief ������Ʈ ������Ƽ�� �����մϴ�.
	 * ����: TICK_PHYSICS | TICK_UPDATE - �Ƚ� Ÿ�� ������Ʈ�� ������ Ÿ�� ������Ʈ�� ƽ�� �����մϴ�.
	 * @param _tickPropertyFlags �÷��� ��Ʈ�� ����
	 */
	void SetTickProperties(TickPropertyFlags _tickPropertyFlags) {
		tickPropertyFlags = _tickPropertyFlags;
	}
	/**
	 * @brief ������Ʈ ������Ƽ�� ��ȯ�մϴ�.
	 * @return ������Ʈ ������Ƽ �÷���
	 */
	TickPropertyFlags GetTickProperties() {
		tickPropertyFlags;
	}

	virtual void FixedUpdate(float _fixedRate) {}
	virtual void PreUpdate(float _dt) {}
	virtual void Update(float _dt) {}
	virtual void PostUpdate(float _dt) {}
	virtual void Render(class D2DRenderer* _renderer) {}
};



