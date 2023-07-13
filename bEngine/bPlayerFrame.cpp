#include "bPlayerFrame.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"

namespace b
{
	PlayerFrame::PlayerFrame()
	{
	}

	PlayerFrame::~PlayerFrame()
	{
	}

	void PlayerFrame::Initialize()
	{
		MeshRenderer* frameMr = this->AddComponent<MeshRenderer>();
		frameMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		frameMr->SetMaterial(Resources::Find<Material>(L"PlayerFrameMaterial"));

		float w = frameMr->GetMaterial()->GetWidth() / 150;
		float h = frameMr->GetMaterial()->GetHeight() / 150;

		this->GetComponent<Transform>()->SetPosition(Vector3(-2.87f, -1.8f, 0.0f));
		this->GetComponent<Transform>()->SetScale(Vector3(w, h, 1.0f));
	}

	void PlayerFrame::Update()
	{
		GameObject::Update();
	}

	void PlayerFrame::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void PlayerFrame::Render()
	{
		GameObject::Render();
	}
}