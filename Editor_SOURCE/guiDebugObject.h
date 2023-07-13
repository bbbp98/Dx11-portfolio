#pragma once
#include "..\\Engine_SOURCE\\bGameObject.h"

namespace gui
{
	class DebugObject : public b::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

