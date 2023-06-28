#include "bLobbyScene.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bCamera.h"
#include "bCameraScript.h"

namespace b
{
	LobbyScene::LobbyScene()
	{
	}

	LobbyScene::~LobbyScene()
	{
	}

	void LobbyScene::Initialize()
	{
		GameObject* bg = new GameObject();
		AddGameObject(eLayerType::BackGround, bg);
		MeshRenderer* bgMr = bg->AddComponent<MeshRenderer>();
		bgMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		bgMr->SetMaterial(Resources::Find<Material>(L"Stage1LobbyBGColorMaterial"));
		bg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.5f, 10.0f));
		bg->GetComponent<Transform>()->SetScale(Vector3(5.0f, 5.0f, 1.0f));

		GameObject* mountain = new GameObject();
		AddGameObject(eLayerType::BackGround, mountain);
		MeshRenderer* mountainMr = mountain->AddComponent<MeshRenderer>();
		mountainMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mountainMr->SetMaterial(Resources::Find<Material>(L"Stage1CatleMaterial"));
		mountain->GetComponent<Transform>()->SetPosition(Vector3(-1.0f, 4.4f, 9.0f));
		mountain->GetComponent<Transform>()->SetScale(Vector3(6.0f, 6.0f, 1.0f));

		GameObject* rampart = new GameObject();
		AddGameObject(eLayerType::BackGround, rampart);
		MeshRenderer* rampartMr = rampart->AddComponent<MeshRenderer>();
		rampartMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		rampartMr->SetMaterial(Resources::Find<Material>(L"Stage1Rampart_BaseMaterial"));
		rampart->GetComponent<Transform>()->SetPosition(Vector3(-2.7f, 1.4f, 7.0f));
		rampart->GetComponent<Transform>()->SetScale(Vector3(1.8f, 2.8f, 1.0f));

		// Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}

	void LobbyScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::O))
			SceneManager::LoadScene(L"TitleScene");
		if (Input::GetKeyDown(eKeyCode::P))
			SceneManager::LoadScene(L"Stage1BossScene");

		Scene::Update();
	}

	void LobbyScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void LobbyScene::Render()
	{
		Scene::Render();
	}
}