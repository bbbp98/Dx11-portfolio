#include "bSceneManager.h"
#include "bTitleScene.h"
#include "bBossScene.h"

namespace b
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;

	void SceneManager::Initialize()
	{
		mActiveScene = new TitleScene();

		mScenes.insert(std::make_pair(L"TitleScene", mActiveScene));
		mScenes.insert(std::make_pair(L"BossScene", new BossScene()));

		//mActiveScene->Initialize();

		for (auto scene : mScenes)
		{
			if (scene.second != nullptr)
				scene.second->Initialize();
		}
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

	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			if (iter.second == nullptr)
				continue;

			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end()) // can't find
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();

		return iter->second;
	}
}