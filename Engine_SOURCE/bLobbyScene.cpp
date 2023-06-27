#include "bLobbyScene.h"
#include "bMeshRenderer.h"
#include "bResources.h"
#include "bTransform.h"
#include "bInput.h"
#include "bSceneManager.h"

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
		AddGameObject(eLayerType::Monster, bg);

		MeshRenderer* bgMr = bg->AddComponent<MeshRenderer>();
		bgMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		bgMr->SetMaterial(Resources::Find<Material>(L"LobbySceneBGMaterial"));

		Transform* tr = bg->GetComponent<Transform>();
		//tr->SetScale(Vector3(4.0f, 3.0f, 3.0f));
	}

	void LobbyScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::O))
			SceneManager::LoadScene(L"TitleScene");
		if (Input::GetKeyDown(eKeyCode::P))
			SceneManager::LoadScene(L"BossScene");

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