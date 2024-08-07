#include "Fireball.h"
#include "FireballProjectile.h"
#include "Player.h"
#include "../D2DGameEngine/BitmapComponent.h"
#include "../D2DGameEngine/CameraComponent.h"
#include "../D2DGameEngine/Mouse.h"
#include "../D2DGameEngine/World.h"


Fireball::Fireball(World* _world) : ProjectileSkill(_world, L"S11000")
{
	SetTickProperties(TICK_UPDATE);

	for (int i = 0; i < projectileMaxCount; i++)
	{
		projectiles.push_back(GetWorld()->GetCurLevel()->CreateActor<FireballProjectile>());
	}
}

Fireball::~Fireball()
{
}

void Fireball::UseSkill()
{
	//���̾ ù ��ġ ����
	Projectile* fireball = projectiles[nowUsingCount];
	fireball->SetLocation(player->GetLocation().x, player->GetLocation().y);

	//���콺 ��ġ�� �̵���Ŵ
	Math::Vector2 mousePos = { Mouse::curMousePosition.x, Mouse::curMousePosition.y };
	mousePos = GetWorld()->ScreenToWorldPoint(mousePos);
	fireball->SetVelocity(mousePos, projectileSpeed);
	
	nowUsingCount++;
}

