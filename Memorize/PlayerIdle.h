#pragma once

#include "PlayerState.h"

class PlayerIdle
	:public PlayerState
{
	// PlayerState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;

	// PlayerState��(��) ���� ��ӵ�
	void Q() override;
	void W() override;
	void E() override;
	void R() override;
	void Left() override;
	void Right() override;
};

