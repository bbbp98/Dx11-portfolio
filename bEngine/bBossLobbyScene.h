#pragma once
#include "bPlayScene.h"

namespace b
{
	class BossLobbyScene : public PlayScene
	{
	public:
		BossLobbyScene();
		~BossLobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

