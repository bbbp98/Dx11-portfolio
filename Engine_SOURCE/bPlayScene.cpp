#include "bPlayScene.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bMesh.h"
#include "CameraScript.h"
#include "bTransform.h"
namespace b
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		GameObject* player = new GameObject();
		AddGameObject(eLayerType::Player, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));

		//player->AddComponent<CameraScript>();

		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
		//tr->SetRotation(Vector3(0.5f, 0.5f, 0.0f));
		tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}