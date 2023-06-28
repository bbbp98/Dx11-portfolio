#pragma once
#include "bSceneManager.h"
#include "bTitleScene.h"
#include "bLobbyScene.h"
#include "bBossScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\bEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\bEngine.lib")
#endif

namespace b
{
	

	void Initializes()
	{
		SceneManager::SetActiveScene(SceneManager::CreateScene<LobbyScene>(L"Stage1LobbyScene"));
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<LobbyScene>(L"Stage1LobbyScene");
		SceneManager::CreateScene<BossScene>(L"Stage1BossScene");
	}
}