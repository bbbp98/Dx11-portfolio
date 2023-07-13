#include "bPlayScene.h"
#include "bCamera.h"
#include "bCameraScript.h"
#include "bPlayerFrame.h"
#include "bTransform.h"
#include "bSceneManager.h"
#include "bSkul.h"
#include "bRenderer.h"
#include "bMeshRenderer.h"
#include "bGridScript.h"
#include "bMesh.h"
#include "bMaterial.h"
#include "bResources.h"

namespace b
{
	PlayScene::PlayScene()
		: mSpeed(1.0f)
		, skul(nullptr)
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		//skul = new Skul();
		//skul->SetName(L"skul");
		//SceneManager::GetActiveScene()->AddGameObject(eLayerType::Player, skul);

		// UI
		PlayerFrame* frame = new PlayerFrame();
		frame->Initialize();
		AddGameObject(eLayerType::UI, frame);

		CreateInCamera();
		CreateMidCamera();
		CreateOutCamera();
		CreateUICamera();

		Scene::Initialize();
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

	void PlayScene::OnEnter()
	{
	}

	void PlayScene::OnExit()
	{
	}

	void PlayScene::CreateInCamera()
	{
		GameObject* camera = new GameObject();
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		cameraComp->DisableLayerMasks();
		cameraComp->TurnLayerMask(eLayerType::BackGround_In);

		//camera->GetComponent<Transform>()->SetParent(skul->GetComponent<Transform>());

		renderer::cameras.push_back(cameraComp);
	}

	void PlayScene::CreateMidCamera()
	{
		GameObject* camera = new GameObject();
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->DisableLayerMasks();
		cameraComp->TurnLayerMask(eLayerType::BackGround_Mid);
		camera->AddComponent<CameraScript>();
		camera->GetComponent<CameraScript>()->SetSpeed(mSpeed);

		renderer::cameras.push_back(cameraComp);
	}

	void PlayScene::CreateOutCamera()
	{
		// main camera
		GameObject* camera = new GameObject();
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
		cameraComp->TurnLayerMask(eLayerType::BackGround_In, false);
		cameraComp->TurnLayerMask(eLayerType::BackGround_Mid, false);
		cameraComp->TurnLayerMask(eLayerType::UI, false);

		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;
	}

	void PlayScene::CreateUICamera()
	{
		GameObject* camera = new GameObject();
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->DisableLayerMasks();
		cameraComp->TurnLayerMask(eLayerType::UI, true);

		renderer::cameras.push_back(cameraComp);
	}
}