#include "bLobbyScene.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bCamera.h"
#include "bCameraScript.h"
#include "bPlayerFrame.h"
#include "bGateWall.h"
#include "bForestBG.h"
#include "bDoor.h"

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
		ForestBG* forestBg = new ForestBG();
		forestBg->Initialize();
		AddGameObject(eLayerType::BackGround_In, forestBg);
		forestBg->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 2.8f, 10.0f));

		GameObject* catle = new GameObject();
		AddGameObject(eLayerType::BackGround_Mid, catle);
		MeshRenderer* catleMr = catle->AddComponent<MeshRenderer>();
		catleMr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		catleMr->SetMaterial(Resources::Find<Material>(L"Stage1CatleMaterial"));
		catle->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 4.9f, 9.0f));
		catle->GetComponent<Transform>()->SetScale(Vector3(6.8f, 7.4f, 1.0f));

		GameObject* tree01 = new GameObject();
		AddGameObject(eLayerType::BackGround_Out, tree01);
		MeshRenderer* tree01Mr = tree01->AddComponent<MeshRenderer>();
		tree01Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		tree01Mr->SetMaterial(Resources::Find<Material>(L"Tree01Material"));
		tree01->GetComponent<Transform>()->SetPosition(Vector3(4.4f, -1.4f, 8.1f));
		tree01->GetComponent<Transform>()->SetScale(Vector3(4.6f, 2.1f, 1.0f));

		GameObject* tree02 = new GameObject();
		AddGameObject(eLayerType::BackGround_Out, tree02);
		MeshRenderer* tree02Mr = tree02->AddComponent<MeshRenderer>();
		tree02Mr->SetMesh(Resources::Find<Mesh>(L"2QuadrantMesh"));
		tree02Mr->SetMaterial(Resources::Find<Material>(L"Tree02Material"));
		tree02->GetComponent<Transform>()->SetPosition(Vector3(0.58f, -0.7f, 8.0f));
		tree02->GetComponent<Transform>()->SetScale(Vector3(2.1f, 0.7f, 1.0f));

		// pillar
		{
			GameObject* pillar01 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, pillar01);
			MeshRenderer* pillar01Mr = pillar01->AddComponent<MeshRenderer>();
			pillar01Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			pillar01Mr->SetMaterial(Resources::Find<Material>(L"Pillar01Material"));
			pillar01->GetComponent<Transform>()->SetPosition(Vector3(-0.87f, 0.12f, 7.9f));
			pillar01->GetComponent<Transform>()->SetScale(Vector3(0.36f, 1.52f, 1.0f));

			GameObject* pillar02 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, pillar02);
			MeshRenderer* pillar02Mr = pillar02->AddComponent<MeshRenderer>();
			pillar02Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			pillar02Mr->SetMaterial(Resources::Find<Material>(L"Pillar02Material"));
			pillar02->GetComponent<Transform>()->SetPosition(Vector3(3.2f, 0.0f, -0.1f));
			pillar02->GetComponent<Transform>()->SetParent(pillar01->GetComponent<Transform>());

			GameObject* pillar03 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, pillar03);
			MeshRenderer* pillar03Mr = pillar03->AddComponent<MeshRenderer>();
			pillar03Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			pillar03Mr->SetMaterial(Resources::Find<Material>(L"Pillar03Material"));
			pillar03->GetComponent<Transform>()->SetPosition(Vector3(3.2f, 0.0f, -0.2f));
			pillar03->GetComponent<Transform>()->SetParent(pillar02->GetComponent<Transform>());

			GameObject* pillar04 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, pillar04);
			MeshRenderer* pillar04Mr = pillar04->AddComponent<MeshRenderer>();
			pillar04Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			pillar04Mr->SetMaterial(Resources::Find<Material>(L"Pillar04Material"));
			pillar04->GetComponent<Transform>()->SetPosition(Vector3(3.2f, 0.0f, -0.3f));
			pillar04->GetComponent<Transform>()->SetParent(pillar03->GetComponent<Transform>());

			GameObject* pillar05 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, pillar05);
			MeshRenderer* pillar05Mr = pillar05->AddComponent<MeshRenderer>();
			pillar05Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			pillar05Mr->SetMaterial(Resources::Find<Material>(L"Pillar04Material"));
			pillar05->GetComponent<Transform>()->SetPosition(Vector3(6.5f, 0.0f, -0.4f));
			pillar05->GetComponent<Transform>()->SetParent(pillar04->GetComponent<Transform>());
		}

		GameObject* rampart = new GameObject();
		AddGameObject(eLayerType::BackGround_Out, rampart);
		MeshRenderer* rampartMr = rampart->AddComponent<MeshRenderer>();
		rampartMr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
		rampartMr->SetMaterial(Resources::Find<Material>(L"Stage1Rampart_BaseMaterial"));
		rampart->GetComponent<Transform>()->SetPosition(Vector3(-2.5f, 1.38f, 7.0f));
		rampart->GetComponent<Transform>()->SetScale(Vector3(1.6f, 2.8f, 1.0f));

		{
			GateWall* gateWall = new GateWall();
			gateWall->Initialize();
			AddGameObject(eLayerType::BackGround_Out, gateWall);
			gateWall->GetComponent<Transform>()->SetPosition(Vector3(3.15f, -0.82f, 6.0f));


			Door* lDoor = new Door();
			lDoor->SetDoorType(Door::eDoorType::Item);
			AddGameObject(eLayerType::BackGround_Out, lDoor);
			lDoor->Initialize();
			lDoor->GetComponent<Transform>()->SetPosition(Vector3(1.3f, -0.58f, 5.1f));

			Door* rDoor = new Door();
			rDoor->SetDoorType(Door::eDoorType::Skul);
			AddGameObject(eLayerType::BackGround_Out, rDoor);
			rDoor->Initialize();
			rDoor->GetComponent<Transform>()->SetPosition(Vector3(5.0f, -0.58f, 5.0f));
		}

		{
			// --------------------------------------------------
			// foretree
			GameObject* foreTree01 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, foreTree01);
			MeshRenderer* foreTree01Mr = foreTree01->AddComponent<MeshRenderer>();
			foreTree01Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			foreTree01Mr->SetMaterial(Resources::Find<Material>(L"Fore_Tree01Material"));
			foreTree01->GetComponent<Transform>()->SetPosition(Vector3(8.45f, 0.85f, 4.0f));
			foreTree01->GetComponent<Transform>()->SetScale(Vector3(3.1f, 3.1f, 1.0f));

			GameObject* fore_Bush02 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, fore_Bush02);
			MeshRenderer* fore_Bush02Mr = fore_Bush02->AddComponent<MeshRenderer>();
			fore_Bush02Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			fore_Bush02Mr->SetMaterial(Resources::Find<Material>(L"Fore_Bush02Material"));
			fore_Bush02->GetComponent<Transform>()->SetPosition(Vector3(-0.72f, -1.57f, 3.7f));
			fore_Bush02->GetComponent<Transform>()->SetScale(Vector3(3.8f, 1.0f, 1.0f));

			GameObject* fore_Bush01 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, fore_Bush01);
			MeshRenderer* fore_Bush01Mr = fore_Bush01->AddComponent<MeshRenderer>();
			fore_Bush01Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			fore_Bush01Mr->SetMaterial(Resources::Find<Material>(L"Fore_Bush01Material"));
			fore_Bush01->GetComponent<Transform>()->SetPosition(Vector3(2.35f, -1.7f, 3.5f));
			fore_Bush01->GetComponent<Transform>()->SetScale(Vector3(5.4f, 0.9f, 1.0f));

			GameObject* fore_Bush04 = new GameObject();
			AddGameObject(eLayerType::BackGround_Out, fore_Bush04);
			MeshRenderer* fore_Bush04Mr = fore_Bush04->AddComponent<MeshRenderer>();
			fore_Bush04Mr->SetMesh(Resources::Find<Mesh>(L"DefaultMesh"));
			fore_Bush04Mr->SetMaterial(Resources::Find<Material>(L"Fore_Bush04Material"));
			fore_Bush04->GetComponent<Transform>()->SetPosition(Vector3(2.1f, -2.0f, 3.8f));
			fore_Bush04->GetComponent<Transform>()->SetScale(Vector3(4.0f, 0.5f, 1.0f));
		}

		// --------------------------------------------------------------
		// UI
		PlayerFrame* frame = new PlayerFrame();
		frame->Initialize();
		AddGameObject(eLayerType::UI, frame);

		{
			// In
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			camera->AddComponent<CameraScript>();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::BackGround_In);

			// Mid
			GameObject* camera2 = new GameObject();
			AddGameObject(eLayerType::Camera, camera2);
			camera2->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* camera2Comp = camera2->AddComponent<Camera>();
			camera2Comp->DisableLayerMasks();
			camera2Comp->TurnLayerMask(eLayerType::BackGround_Mid);
			camera2->AddComponent<CameraScript>();
			camera2->GetComponent<CameraScript>()->SetSpeed(0.6f);

			// Others
			GameObject* camera3 = new GameObject();
			AddGameObject(eLayerType::Camera, camera3);
			camera3->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* camera3Comp = camera3->AddComponent<Camera>();
			camera3->AddComponent<CameraScript>();
			camera3Comp->TurnLayerMask(eLayerType::BackGround_In, false);
			camera3Comp->TurnLayerMask(eLayerType::BackGround_Mid, false);
			camera3Comp->TurnLayerMask(eLayerType::UI, false);

			// UI Camera
			GameObject* UICamera = new GameObject();
			AddGameObject(eLayerType::Camera, UICamera);
			UICamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* UICameraComp = UICamera->AddComponent<Camera>();
			UICameraComp->DisableLayerMasks();
			UICameraComp->TurnLayerMask(eLayerType::UI, true);
		}
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