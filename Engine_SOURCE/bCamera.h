#pragma once
#include "bComponent.h"
#include "bGraphics.h"

namespace b
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

	private:
		static Matrix mView;
		static Matrix mProjection;
	};
}

