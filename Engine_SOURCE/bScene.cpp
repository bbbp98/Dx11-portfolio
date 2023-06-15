#include "bScene.h"

namespace b
{
	Scene::Scene()
		: mLayers{}
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		// 초기 게임 맵 데이터 세팅
	}

	void Scene::Update()
	{
		for (Layer* layer : mLayers)
		{
			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayers)
		{
			layer->LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer* layer : mLayers)
		{
			layer->Render();
		}
	}
}