#include "bBossScene.h"
#include "bGameObject.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bCamera.h"
#include "bTransform.h"
#include "CameraScript.h"
#include "bSceneManager.h"
#include "bInput.h"

namespace b
{
	BossScene::BossScene()
	{
	}

	BossScene::~BossScene()
	{
	}

	void BossScene::Initialize()
	{
		GameObject* bg = new GameObject();
		AddGameObject(eLayerType::UI, bg);

		MeshRenderer* bgMr = bg->AddComponent<MeshRenderer>();
		bgMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		bgMr->SetMaterial(Resources::Find<Material>(L"BossSceneBGMaterial"));

		Transform* tr = bg->GetComponent<Transform>();
		tr->SetScale(Vector3(4.0f, 3.0f, 3.0f));

		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}

	void BossScene::Update()
	{
		if (Input::GetKey(eKeyCode::O))
			SceneManager::LoadScene(L"TitleScene");

		Scene::Update();
	}

	void BossScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void BossScene::Render()
	{
		Scene::Render();
	}
}