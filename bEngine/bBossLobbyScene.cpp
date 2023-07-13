#include "bBossLobbyScene.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"
#include "bCloud.h"
#include "bCloudScript.h"

namespace b
{
	BossLobbyScene::BossLobbyScene()
	{
	}

	BossLobbyScene::~BossLobbyScene()
	{
	}

	void BossLobbyScene::Initialize()
	{
		GameObject* bgColor = new GameObject();
		AddGameObject(eLayerType::BackGround_In, bgColor);
		MeshRenderer* bgColorMr = bgColor->AddComponent<MeshRenderer>();
		bgColorMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		bgColorMr->SetMaterial(Resources::Find<Material>(L"S1BossLobbyBGColorMaterial"));
		bgColor->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 3.0f, 20.0f));
		bgColor->GetComponent<Transform>()->SetScale(Vector3(6.0f, 5.0f, 1.0f));
		
		// cloud
		{
			Cloud* smallClouds = new Cloud();
			AddGameObject(eLayerType::BackGround_In, smallClouds);
			MeshRenderer* smallCloudsMr = smallClouds->GetComponent<MeshRenderer>();
			smallCloudsMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			smallCloudsMr->SetMaterial(Resources::Find<Material>(L"cloud07Material"));
			smallClouds->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.8f, 19.9f));
			smallClouds->GetComponent<Transform>()->SetScale(Vector3(4.0f, 1.0f, 1.0f));
			smallClouds->GetComponent<CloudScript>()->SetSpeed(0.25f);

			Cloud* bigCloud = new Cloud();
			AddGameObject(eLayerType::BackGround_In, bigCloud);
			MeshRenderer* bigCloudMr = bigCloud->GetComponent<MeshRenderer>();
			bigCloudMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			bigCloudMr->SetMaterial(Resources::Find<Material>(L"cloud06Material"));
			bigCloud->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.2f, 19.8f));
			bigCloud->GetComponent<Transform>()->SetScale(Vector3(2.0f, 0.5f, 1.0f));
		}

		GameObject* bg = new GameObject();
		AddGameObject(eLayerType::BackGround_Mid, bg);
		MeshRenderer* bgMr = bg->AddComponent<MeshRenderer>();
		bgMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		bgMr->SetMaterial(Resources::Find<Material>(L"S1BossLobbyBGMaterial"));
		bg->GetComponent<Transform>()->SetPosition(Vector3(1.1f, 0.0f, 19.5f));
		bg->GetComponent<Transform>()->SetScale(Vector3(5.8f, 1.7f, 1.0f));
		bg->GetComponent<Transform>()->SetStartUV(Vector2(0.8f, 0.0f));

		GameObject* bgTree = new GameObject();
		AddGameObject(eLayerType::BackGround_Mid, bgTree);
		MeshRenderer* bgTreeMr = bgTree->AddComponent<MeshRenderer>();
		bgTreeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		bgTreeMr->SetMaterial(Resources::Find<Material>(L"BossLobbyBGTreeMaterial"));
		bgTree->GetComponent<Transform>()->SetPosition(Vector3(1.45f, 0.0f, 19.4f));
		bgTree->GetComponent<Transform>()->SetScale(Vector3(5.8f, 2.0f, 1.0f));

		// 보스 문 앞


		PlayScene::SetSpeed(1.2f);
		PlayScene::Initialize();
	}

	void BossLobbyScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::O))
			SceneManager::LoadScene(L"Stage1LobbyScene");
		if (Input::GetKeyDown(eKeyCode::P))
			SceneManager::LoadScene(L"Stage1BossScene");

		PlayScene::Update();
	}

	void BossLobbyScene::LateUpdate()
	{
		PlayScene::LateUpdate();
	}

	void BossLobbyScene::Render()
	{
		PlayScene::Render();
	}
}