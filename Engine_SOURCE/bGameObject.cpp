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
		// �� ������ ����
	}

	void GameObject::LateUpdate()
	{
	}

	void GameObject::Render()
	{
		// ��� ���۷� ��ġ, ũ��, ���� ���� ������Ʈ
		//renderer::mesh->BindBuffer();
		//renderer::shader->Binds();
		//graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}