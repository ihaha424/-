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
	 * @brief ��Ʈ�ѷ��� �����մϴ�.
	 * @param _controller 
	 */
	virtual void PossessedBy(class Controller* _controller);
};

