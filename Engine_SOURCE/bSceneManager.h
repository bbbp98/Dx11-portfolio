#pragma once
#include "bScene.h"

namespace b
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();
		static void Release();

		template <typename T>
		static T* CreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

			if (iter != mScenes.end())
				return nullptr;

			mScenes.insert(std::make_pair(name, scene));
			//mActiveScene = scene;
			scene->Initialize();
			return scene;
		}

		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* LoadScene(std::wstring name);

	private:
		static Scene* mActiveScene;
		static std::map<std::wstring, Scene*> mScenes;
	};
}

