#pragma once
#include "bScene.h"
#include "bSkul.h"

namespace b
{
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void SetSpeed(float speed) { mSpeed = speed; }

	private:
		void CreateInCamera();
		void CreateMidCamera();
		void CreateOutCamera();
		void CreateUICamera();

		float mSpeed;

		Skul* skul;
	};
}

