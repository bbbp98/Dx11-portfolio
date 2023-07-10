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

		static Matrix GetViewMatrix() { return View; }
		static Matrix GetProjectionMatrix() { return Projection; }

		Camera();
		~Camera();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);

		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnableLayerMasks() { mLayerMask.set(); }
		void DisableLayerMasks() { mLayerMask.reset(); }

		void AlphaSortGameObjects();
		void ZSortGameObjects();
		void DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs);

		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisableDepthStencilState();

		float GetSize() { return mSize; }

		void Clear();

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;
		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
	};
}

