#include "bDoor.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"

namespace b
{
	Door::Door()
		: mType(eDoorType::None)
	{
	}

	Door::~Door()
	{
	}

	void Door::Initialize()
	{
		MeshRenderer* doorMr = this->AddComponent<MeshRenderer>();
		doorMr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));

		switch (mType)
		{
		case b::Door::eDoorType::None:
			doorMr->SetMaterial(Resources::Find<Material>(L"S1ItemDoorMt"));
			break;
		case b::Door::eDoorType::Item:
			doorMr->SetMaterial(Resources::Find<Material>(L"S1ItemDoorMt"));
			break;
		case b::Door::eDoorType::Gold:
			doorMr->SetMaterial(Resources::Find<Material>(L"S1GoldDoorMt"));
			break;
		case b::Door::eDoorType::Skul:
			doorMr->SetMaterial(Resources::Find<Material>(L"S1SkulDoorMt"));
			break;
		case b::Door::eDoorType::Boss:
			break;
		case b::Door::eDoorType::BossLobby:
			break;
		case b::Door::eDoorType::MiddleBoss:
			break;
		case b::Door::eDoorType::Shop:
			break;
		default:
			break;
		}

		Transform* parent = GetComponent<Transform>()->GetParent();
		float w = doorMr->GetMaterial()->GetWidth() / 150;
		float h = doorMr->GetMaterial()->GetHeight() / 150;

		this->GetComponent<Transform>()->SetScale(Vector3(w, h, 1.0f));

	}

	void Door::Update()
	{
		GameObject::Update();
	}

	void Door::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Door::Render()
	{
		GameObject::Render();
	}
}