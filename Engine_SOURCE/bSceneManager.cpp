#include "bSceneManager.h"
#include "bPlayScene.h"

namespace b
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mActiveScene = new PlayScene();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
}