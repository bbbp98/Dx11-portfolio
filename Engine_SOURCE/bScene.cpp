#include "bScene.h"
#include "bTime.h"

namespace b
{
	float time = 0.0f;
	Scene::Scene()
		: mGameObjects{}
	{
	}

	Scene::~Scene()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			delete gameObj;
		}
	}

	void Scene::Initialize()
	{
		// 초기 게임 맵 데이터 세팅
		mGameObjects.push_back(new GameObject());
		mGameObjects[0]->SetName(L"player");
		mGameObjects[0]->SetScale(0.8f);

		for (size_t i = 1; i < 10; i++)
		{
			mGameObjects.push_back(new GameObject());
			mGameObjects[i]->SetPos();
			mGameObjects[i]->SetColor();
			mGameObjects[i]->SetScale(0.5f);
		}

		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj != nullptr)
				gameObj->Initialize();
		}
	}

	void Scene::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj != nullptr)
				gameObj->Update();
		}

		for (size_t i = 1; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] == nullptr)
				continue;

			float len = mGameObjects[0]->GetLength() + mGameObjects[i]->GetLength();
			float distX = mGameObjects[0]->GetPos().x - mGameObjects[i]->GetPos().x;
			float distY = mGameObjects[0]->GetPos().y - mGameObjects[i]->GetPos().y;
			float dist = pow(distX, 2) + pow(distY, 2);
			dist = sqrt(dist);

			if (len >= dist)
			{
				// delete object, scale up player
				delete mGameObjects[i];
				mGameObjects[i] = nullptr;

				mGameObjects[0]->SetScale(0.1f);
			}
		}

		time += Time::DeltaTime();

		if (time >= 1.5f)
		{
			mGameObjects.push_back(new GameObject());
			mGameObjects[mGameObjects.size() - 1]->SetPos();
			mGameObjects[mGameObjects.size() - 1]->SetColor();
			mGameObjects[mGameObjects.size() - 1]->SetScale(0.5f);

			time = 0.0f;
		}
	}

	void Scene::LateUpdate()
	{
		
	}

	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj != nullptr)
				gameObj->Render();
		}
	}
}