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
		GameObject* backGround = new GameObject();
		AddGameObject(eLayerType::BackGround, backGround);
		MeshRenderer* bgMr = backGround->AddComponent<MeshRenderer>();
		bgMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		bgMr->SetMaterial(Resources::Find<Material>(L"TitleBGMaterial"));
		backGround->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		backGround->GetComponent<Transform>()->SetScale(Vector3(4.0f, 2.4f, 1.0f));


		GameObject* logo = new GameObject();
		AddGameObject(eLayerType::BackGround, logo);
		MeshRenderer* logoMr = logo->AddComponent<MeshRenderer>();
		logoMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		logoMr->SetMaterial(Resources::Find<Material>(L"TitleLogoMaterial"));
		logo->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -1.2f, -1.0f));
		logo->GetComponent<Transform>()->SetScale(Vector3(1.4f, 0.6f, 1.0f));



		// Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
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