#pragma once
#include "bScene.h"

namespace b
{
	class PlayScene : public Scene
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:

	};
}

