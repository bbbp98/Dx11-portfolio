#pragma once
#include "bPlayScene.h"

namespace b
{
	class LobbyScene : public PlayScene
	{
	public:
		LobbyScene();
		~LobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:

	};
}

