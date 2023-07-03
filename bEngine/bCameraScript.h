#pragma once
#include "bScript.h"

namespace b
{
	class CameraScript : public Script
	{
	public:
		virtual void Update() override;

		void SetSpeed(float speed) { mSpeed = speed; }

	private:
		float mSpeed = 1.0f;
	};
}

