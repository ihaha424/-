#pragma once

#include "PlayerState.h"

class PlayerIdle
	:public PlayerState
{
public:
	PlayerIdle(FSMComponent* _owner, std::wstring _name)
		:PlayerState(_owner, _name)
	{}
	virtual ~PlayerIdle() {};

	// PlayerState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;

};

