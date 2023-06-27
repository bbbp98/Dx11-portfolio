#include "bTitleScene.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bMesh.h"
#include "CameraScript.h"
#include "bTransform.h"
#include "bCamera.h"
#include "bInput.h"
#include "bSceneManager.h"

namespace b
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		GameObject* player = new GameObject();
		AddGameObject(eLayerType::Player, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleBGMaterial"));

		//player->AddComponent<CameraScript>();

		Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
		//tr->SetRotation(Vector3(0.5f, 0.5f, 0.0f));
		//tr->SetScale(Vector3(4.0f, 2.4f, 1.0f));


		// Main Camera
		//GameObject* camera = new GameObject();
		//AddGameObject(eLayerType::Player, camera);
		//camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//Camera* cameraComp = camera->AddComponent<Camera>();
		//camera->AddComponent<CameraScript>();
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::P))
			SceneManager::LoadScene(L"LobbyScene");
		Scene::Update();
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}
}