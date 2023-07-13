#include "bGateWall.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"

namespace b
{
	GateWall::GateWall()
	{
	}

	GateWall::~GateWall()
	{
	}

	void GateWall::Initialize()
	{
		MeshRenderer* gateWallMr = this->AddComponent<MeshRenderer>();
		gateWallMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gateWallMr->SetMaterial(Resources::Find<Material>(L"Ch1_Gate_WallMaterial"));

		float w = gateWallMr->GetMaterial()->GetWidth() / 162;
		float h = gateWallMr->GetMaterial()->GetHeight() / 162;

		this->GetComponent<Transform>()->SetScale(Vector3(w, h, 1.0f));

		// ���� �ڽ����� �ٿ��� rand ������ Ÿ�Կ� ���� ��ġ
		//Door* lDoor = new Door();
		//lDoor->SetDoorType(Door::eDoorType::Item);
		//lDoor->GetComponent<Transform>()->SetParent(this->GetComponent<Transform>());
		//lDoor->GetComponent<Transform>()->SetPosition(Vector3(-1.0f, 0.0f, -0.1f));
		//lDoor->Initialize();
		//SceneManager::GetActiveScene()->AddGameObject(eLayerType::BackGround_Out, lDoor);

		//Door* rDoor = new Door();
		//rDoor->SetDoorType(Door::eDoorType::Gold);
		//rDoor->GetComponent<Transform>()->SetParent(this->GetComponent<Transform>());
		//rDoor->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, -0.2f));
		//rDoor->Initialize();
		//SceneManager::GetActiveScene()->AddGameObject(eLayerType::BackGround_Out, rDoor);
	}

	void GateWall::Update()
	{
		GameObject::Update();
	}

	void GateWall::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void GateWall::Render()
	{
		GameObject::Render();
	}
}