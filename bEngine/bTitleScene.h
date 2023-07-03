#pragma once
#include "bScene.h"

namespace b
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void OnExit() override;
		void OnEnter() override;

	private:

	};
}

