#include "framework.h"
#include "Level.h"

Level::Level(const std::wstring& name)
{
	LevelName = name;
}

Level::~Level()
{
	for (auto& pGameObject : vGameObjectList)
	{
		delete pGameObject;
	}
	vGameObjectList.clear();
}

void Level::Update(const float& deltaTime)
{
	for (auto objList : vGameObjectList)
	{
		//objList->SuperUpdate(deltaTime);
	}
}

void Level::LateUpdate(const float& deltaTime)
{
	for (auto objList : vGameObjectList)
	{
		//objList->SuperLateUpdate(deltaTime);
	}

	////MouseUpdate...
	//MouseComponent::GetInstance()->Update(deltaTime);
}

void Level::PhysicalUpdate()
{
	//colliderManager.Update(vGameObjectList);
}

void Level::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto objList : vGameObjectList)
	{
		//objList->SuperRender(pRenderTarget);
	}

	//
	//	UI Update
	//

	// MainMouse -> �� ���콺�� �ٸ����� ������Ʈ�� �� ���� ��ī��?
	// Update�� �� ���ϳ�?
	// Level���� Mouse�� �θ� ������Ʈ�� ��� �־�� �ϳ�?
	//MouseComponent::GetInstance()->Render(pRenderTarget);
}