#include "bGameObject.h"
#include "bRenderer.h"
#include "bGraphicDevice_DX11.h"

namespace b
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		// 공 움직임 구현
	}

	void GameObject::LateUpdate()
	{
	}

	void GameObject::Render()
	{
		// 상수 버퍼로 위치, 크기, 색깔 정보 업데이트
		//renderer::mesh->BindBuffer();
		//renderer::shader->Binds();
		//graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}