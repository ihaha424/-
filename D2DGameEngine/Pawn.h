#pragma once
#include "Actor.h"
#include "SimpleMath.h"

class Pawn : public Actor
{
	class Controller* controller = nullptr;

public:
	Pawn();
	virtual ~Pawn();

	/**
	 * @brief ��Ʈ�ѷ��� ��ȯ�մϴ�. 
	 * @return controller
	 */
	class Controller* GetController() const { return controller; };

	/**
	 * @brief ��Ʈ�ѷ��� �����մϴ�.
	 * @param _controller
	 */
	void SetController(class Controller* _controller) { controller = _controller; }
};

