#include "PlayerState.h"
#include "D2DGameEngine/World.h"
#include "D2DGameEngine/FSMComponent.h"
#include "D2DGameEngine/Mouse.h"
#include "MovementComponent.h"
#include "GPlayerController.h"
#include "Player.h"


#include "Fireball.h"

void PlayerState::Fire()
{
	GPlayerController* playerController = static_cast<GPlayerController*>(owner->GetOwner());
	playerController->StartSkill<Fireball>();
}

void PlayerState::Water()
{
}

void PlayerState::Light()
{
}

void PlayerState::Dark()
{
}

void PlayerState::Attack()
{
	//�⺻����
}

#include "D2DGameEngine/Debug.h"

void PlayerState::Move()
{
	GPlayerController* playerController = static_cast<GPlayerController*>(owner->GetOwner());
	Math::Vector2 destPos = playerController->GetWorld()->ScreenToWorldPoint({ Mouse::curMousePosition.x, Mouse::curMousePosition.y });
	Math::Vector2 direction = destPos - playerController->GetPlayer()->GetLocation();
	direction.Normalize();
	playerController->GetPlayer()->GetComponent<MovementComponent>()->SetDirection(direction);
	playerController->GetPlayer()->GetComponent<MovementComponent>()->SetSpeed(500.0f);

	LOG_INFO(dbg::text(destPos.x, ", ", destPos.y));
}

void PlayerState::Memorize()
{
	// if()// �÷��̾ ������ ������ ������...)
	//owner->SetNextState(L"PlayerAttack");
	//������ ���� ������  Player �� ��� �ִ�.
}
