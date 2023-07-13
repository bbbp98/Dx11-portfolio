#include "bSkul.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"
#include "bInput.h"
#include "bTime.h"

namespace b
{
	Skul::Skul()
	{
	}

	Skul::~Skul()
	{
	}

	void Skul::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SkulIdle"));
		GetComponent<Transform>()->SetScale(0.5f, 0.5f, 1.0f);
		GameObject::Initialize();
	}

	void Skul::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::LEFT))
			pos.x -= 0.5f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::RIGHT))
			pos.x += 0.5f * Time::DeltaTime();

		tr->SetPosition(pos);

		GameObject::Update();
	}

	void Skul::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Skul::Render()
	{
		GameObject::Render();
	}
}