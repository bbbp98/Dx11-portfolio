#include "bScene.h"

namespace b
{
	Scene::Scene()
	{
		mLayers.resize((int)b::enums::eLayerType::End);
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		// 초기 게임 맵 데이터 세팅
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}

	void Scene::OnEnter()
	{
	}

	void Scene::OnExit()
	{
	}

	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
	}
}