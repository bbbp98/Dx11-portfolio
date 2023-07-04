#pragma once
#include "bScript.h"
#include "bGraphics.h"

namespace b
{
	class CloudScript : public Script
	{
	public:
		virtual void Update() override;

		void SetSpeed(float speed) { mSpeed = speed; }

	private:
		float mSpeed = 1.0f;
	};
}

