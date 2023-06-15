#pragma once
#include "bComponent.h"

namespace b
{
	using namespace b::math;
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		struct Data
		{
			Vector4 pos;
			Vector4 color;
			float scale;
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void SetPos();
		void SetColor();
		void SetScale(float scale);

		float GetLength() { return 0.1f * mData.scale; }
		Vector4 GetPos() { return mData.pos; }

	private:
		eState mState;
		Data mData;
	};
}

