#include "bForestBG.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"

namespace b
{
	ForestBG::ForestBG()
	{
	}

	ForestBG::~ForestBG()
	{
	}

	void ForestBG::Initialize()
	{
		MeshRenderer* forestMr = this->AddComponent<MeshRenderer>();
		forestMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		forestMr->SetMaterial(Resources::Find<Material>(L"forestBGMaterial"));

		float w = forestMr->GetMaterial()->GetWidth() / 120;
		float h = forestMr->GetMaterial()->GetHeight() / 120;

		this->GetComponent<Transform>()->SetScale(Vector3(w, h, 1.0f));
	}

	void ForestBG::Update()
	{
		GameObject::Update();
	}

	void ForestBG::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void ForestBG::Render()
	{
		GameObject::Render();
	}
}