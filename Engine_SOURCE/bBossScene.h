#pragma once
#include "bScene.h"

namespace b
{
	class BossScene : public Scene
	{
	public:
		BossScene();
		~BossScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:

	};
}

