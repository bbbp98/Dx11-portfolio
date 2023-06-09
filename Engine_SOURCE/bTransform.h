#pragma once
#include "bComponent.h"

namespace b
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void BindConstantBuffer();

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetRotation(Vector3 rotation)
		{ 
			mRotation.x = XM_PI / (180.0f / rotation.x); 
			mRotation.y = XM_PI / (180.0f / rotation.y); 
			mRotation.z = XM_PI / (180.0f / rotation.z); 
		}
		void SetScale(Vector3 scale) { mScale = scale; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z)
		{
			//mRotation = Vector3(x, y, z);
			mRotation.x = XM_PI / (180.0f / x);
			mRotation.y = XM_PI / (180.0f / y);
			mRotation.z = XM_PI / (180.0f / z);
		}
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		Vector3 GetPosition() { return mPosition; }
		Vector3 GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() { return mParent; }

		void SetStartUV(Vector2 uv) { mStartUV = uv; }

	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Vector3 mUp;
		Vector3 mFoward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;

		Vector2 mStartUV;
	};
}

