#pragma once
#include "bScene.h"

namespace b
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render();

	private:
		int mIndex[3];

		HDC mHdc;
	};
}

