#pragma once

#include "../D2DGameEngine/FSMState.h"

class PlayerState
	:FSMState
{
public:
	PlayerState();
	~PlayerState();


	virtual void Q() {}
	virtual void W() {}
	virtual void E() {}
	virtual void R() {}
	virtual void Left() {}
	virtual void Right() {}

	// FSMState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;
};

