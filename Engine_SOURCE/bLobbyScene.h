#pragma once
#include "bScene.h"

namespace b
{
	class LobbyScene : public Scene
	{
	public:
		LobbyScene();
		~LobbyScene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:

	};
}

