#pragma once
#include "bScene.h"

namespace b
{
	class SceneManager
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		static Scene* mActiveScene;
	};
}

