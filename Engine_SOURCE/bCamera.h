#pragma once
#include "bComponent.h"
#include "bGraphics.h"

namespace b
{
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perpective,
			Orthographic,
			None,
		};

		static Matrix GetViewMatrix() { return mView; }
		static Matrix GetProjectionMatrix() { return mProjection; }

		Camera();
		~Camera();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);

	private:
		static Matrix mView;
		static Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;
	};
}

