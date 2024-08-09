#include "Fireball.h"
#include "FireballProjectile.h"
#include "Player.h"
#include "../D2DGameEngine/BitmapComponent.h"
#include "../D2DGameEngine/CameraComponent.h"
#include "../D2DGameEngine/Mouse.h"
#include "../D2DGameEngine/World.h"


Fireball::Fireball(Actor* _owner) : ProjectileSkill(_owner)
{
	SetTickProperties(TICK_UPDATE);

	projectileMaxCount = 5;

	for (int i = 0; i < projectileMaxCount; i++)
	{
		projectiles.push_back(GetWorld()->GetCurLevel()->CreateActor<FireballProjectile>());
		projectiles[i]->SetVelocity({ 0,0 }, 0);
	}
}

Fireball::~Fireball()
{
}

void Fireball::BeginPlay()
{
	__super::BeginPlay();
	
	for (int i = 0; i < projectileMaxCount; i++)
	{
		projectiles[i]->SetStatus(OS_INACTIVE);
	}
}

void Fireball::UseSkill()
{
	__super::UseSkill();

	//���̾ ù ��ġ ����
	Projectile* fireball = projectiles[nowUsingCount];
	fireball->SetOwner(player);
	fireball->SetLocation(player->GetLocation().x, player->GetLocation().y);
	fireball->SetStatus(OS_ACTIVE);

	//���콺 ��ġ�� �̵���Ŵ
	Math::Vector2 mousePos = { Mouse::curMousePosition.x, Mouse::curMousePosition.y };
	mousePos = GetWorld()->ScreenToWorldPoint(mousePos);
	Math::Vector2 direction = mousePos - Math::Vector2( player->GetLocation().x , player->GetLocation().y  ) ;
	direction.Normalize();
	fireball->SetVelocity(direction, projectileSpeed);
	
	nowUsingCount++;
}

