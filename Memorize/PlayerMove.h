#pragma once
#include "PlayerState.h"

class PlayerMove
	:public PlayerState
{
public:
	PlayerMove(FSMComponent* _owner, std::wstring _name)
		:PlayerState(_owner, _name)
	{}
	virtual ~PlayerMove() {};

	// PlayerState��(��) ���� ��ӵ�
	void Enter() override;
	void Update(float _dt) override;
	void Exit() override;

};