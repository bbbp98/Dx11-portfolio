#pragma once
#include "bSceneManager.h"
#include "bTitleScene.h"
#include "bPlayScene.h"
#include "bLobbyScene.h"
#include "bBossScene.h"
#include "bBossLobbyScene.h"
#include "bToolScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\bEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\bEngine.lib")
#endif

namespace b
{
	

	void Initializes()
	{
		SceneManager::CreateScene<ToolScene>(L"ToolScene");
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<LobbyScene>(L"Stage1LobbyScene");
		SceneManager::CreateScene<BossLobbyScene>(L"Stage1BossLobbyScene");
		SceneManager::CreateScene<BossScene>(L"Stage1BossScene");

		SceneManager::LoadScene(L"ToolScene");
	}
}