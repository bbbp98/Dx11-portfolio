#include "bGameObject.h"
#include "bRenderer.h"
#include "bGraphicDevice_DX11.h"
#include "bInput.h"
#include "bConstantBuffer.h"

namespace b
{
	//ConstantBuffer* csBuffer;
	GameObject::GameObject()
		: mState(eState::Active)
		, mData{}
	{
		mData.pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		mData.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		mData.scale = 0.0f;
	}

	GameObject::~GameObject()
	{
		//delete csBuffer;
	}

	void GameObject::Initialize()
	{
		//renderer::constantBuffer = new ConstantBuffer(eCBType::Transform);
		//renderer::constantBuffer->Create(sizeof(Vector4) * 3);
	}

	void GameObject::Update()
	{
		// 공 움직임 구현
		if (this->GetName() == L"player")
		{
			if (Input::GetKey(eKeyCode::LEFT))
			{
				mData.pos.x -= 0.0005f;
			}

			if (Input::GetKey(eKeyCode::RIGHT))
			{
				mData.pos.x += 0.0005f;
			}

			if (Input::GetKey(eKeyCode::UP))
			{
				mData.pos.y += 0.0005f;
			}

			if (Input::GetKey(eKeyCode::DOWN))
			{
				mData.pos.y -= 0.0005f;
			}
		}
		
	}

	void GameObject::LateUpdate()
	{
		
	}

	void GameObject::Render()
	{
		// 상수 버퍼로 위치, 크기, 색깔 정보 업데이트
		renderer::constantBuffer->SetData(&mData);
		renderer::constantBuffer->Bind(eShaderStage::VS);
		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}

	void GameObject::SetPos()
	{
		std::vector<int> res = mrand(2, 200);

		for (size_t i = 0; i < res.size(); i++)
		{
			if (res[i] >= 1)
				res[i] -= 100;
		}

		mData.pos.x = (float)res[0] / 100;
		mData.pos.y = (float)res[1] / 100;
	}

	void GameObject::SetColor()
	{
		std::vector<int> res = mrand(3, 100);

		mData.color.x = (float)res[0] / 100;
		mData.color.y = (float)res[1] / 100;
		mData.color.z = (float)res[2] / 100;
	}

	void GameObject::SetScale(float scale)
	{
		mData.scale += scale;
	}
}