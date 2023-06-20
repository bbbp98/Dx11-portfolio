#include "bGameObject.h"
#include "bRenderer.h"
#include "bGraphicDevice_DX11.h"
#include "bTransform.h"
namespace b
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		// 공 움직임 구현
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			comp->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		// 상수 버퍼로 위치, 크기, 색깔 정보 업데이트
		for (Component* comp : mComponents)
		{
			comp->Render();
		}
	}
}