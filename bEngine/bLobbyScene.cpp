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
		bgMr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		bgMr->SetMaterial(Resources::Find<Material>(L"Stage1LobbyBGColorMaterial"));
		bg->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 2.5f, 10.0f));
		bg->GetComponent<Transform>()->SetScale(Vector3(6.5f, 6.5f, 1.0f));

		GameObject* catle = new GameObject(); // need to camera move
		AddGameObject(eLayerType::BackGround, catle);
		MeshRenderer* catleMr = catle->AddComponent<MeshRenderer>();
		catleMr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		catleMr->SetMaterial(Resources::Find<Material>(L"Stage1CatleMaterial"));
		catle->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 4.9f, 9.0f));
		catle->GetComponent<Transform>()->SetScale(Vector3(6.8f, 7.4f, 1.0f));
		
		GameObject* tree01 = new GameObject();
		AddGameObject(eLayerType::BackGround, tree01);
		MeshRenderer* tree01Mr = tree01->AddComponent<MeshRenderer>();
		tree01Mr->SetMesh(Resources::Find<Mesh>(L"2QuadrantMesh"));
		tree01Mr->SetMaterial(Resources::Find<Material>(L"Tree01Material"));
		tree01->GetComponent<Transform>()->SetPosition(Vector3(2.2f, -0.2f, 8.1f));
		tree01->GetComponent<Transform>()->SetScale(Vector3(2.2f, 1.1f, 1.0f));

		GameObject* tree02 = new GameObject();
		AddGameObject(eLayerType::BackGround, tree02);
		MeshRenderer* tree02Mr = tree02->AddComponent<MeshRenderer>();
		tree02Mr->SetMesh(Resources::Find<Mesh>(L"2QuadrantMesh"));
		tree02Mr->SetMaterial(Resources::Find<Material>(L"Tree02Material"));
		tree02->GetComponent<Transform>()->SetPosition(Vector3(0.58f, -0.7f, 8.0f));
		tree02->GetComponent<Transform>()->SetScale(Vector3(2.1f, 0.7f, 1.0f));
		

		GameObject* pillar01 = new GameObject();
		AddGameObject(eLayerType::BackGround, pillar01);
		MeshRenderer* pillar01Mr = pillar01->AddComponent<MeshRenderer>();
		pillar01Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		pillar01Mr->SetMaterial(Resources::Find<Material>(L"Pillar01Material"));
		pillar01->GetComponent<Transform>()->SetPosition(Vector3(-0.87f, 0.12f, 7.9f));
		pillar01->GetComponent<Transform>()->SetScale(Vector3(0.36f, 1.52f, 1.0f));

		GameObject* pillar02 = new GameObject();
		AddGameObject(eLayerType::BackGround, pillar02);
		MeshRenderer* pillar02Mr = pillar02->AddComponent<MeshRenderer>();
		pillar02Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		pillar02Mr->SetMaterial(Resources::Find<Material>(L"Pillar02Material"));
		pillar02->GetComponent<Transform>()->SetPosition(Vector3(0.32f, 0.12f, 7.9f));
		pillar02->GetComponent<Transform>()->SetScale(Vector3(0.36f, 1.52f, 1.0f));

		GameObject* pillar03 = new GameObject();
		AddGameObject(eLayerType::BackGround, pillar03);
		MeshRenderer* pillar03Mr = pillar03->AddComponent<MeshRenderer>();
		pillar03Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		pillar03Mr->SetMaterial(Resources::Find<Material>(L"Pillar03Material"));
		pillar03->GetComponent<Transform>()->SetPosition(Vector3(1.51f, 0.12f, 7.9f));
		pillar03->GetComponent<Transform>()->SetScale(Vector3(0.36f, 1.52f, 1.0f));

		GameObject* pillar04 = new GameObject();
		AddGameObject(eLayerType::BackGround, pillar04);
		MeshRenderer* pillar04Mr = pillar04->AddComponent<MeshRenderer>();
		pillar04Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		pillar04Mr->SetMaterial(Resources::Find<Material>(L"Pillar04Material"));
		pillar04->GetComponent<Transform>()->SetPosition(Vector3(2.7f, 0.12f, 7.9f));
		pillar04->GetComponent<Transform>()->SetScale(Vector3(0.36f, 1.52f, 1.0f));

		GameObject* pillar05 = new GameObject();
		AddGameObject(eLayerType::BackGround, pillar05);
		MeshRenderer* pillar05Mr = pillar05->AddComponent<MeshRenderer>();
		pillar05Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		pillar05Mr->SetMaterial(Resources::Find<Material>(L"Pillar04Material"));
		pillar05->GetComponent<Transform>()->SetPosition(Vector3(5.1f, 0.12f, 7.9f));
		pillar05->GetComponent<Transform>()->SetScale(Vector3(0.36f, 1.52f, 1.0f));
		
		GameObject* rampart = new GameObject();
		AddGameObject(eLayerType::BackGround, rampart);
		MeshRenderer* rampartMr = rampart->AddComponent<MeshRenderer>();
		rampartMr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		rampartMr->SetMaterial(Resources::Find<Material>(L"Stage1Rampart_BaseMaterial"));
		rampart->GetComponent<Transform>()->SetPosition(Vector3(-2.5f, 1.38f, 7.0f));
		rampart->GetComponent<Transform>()->SetScale(Vector3(1.6f, 2.8f, 1.0f));


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