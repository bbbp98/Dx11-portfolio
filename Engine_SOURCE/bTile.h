#pragma once
#include "bGameObject.h"

namespace b
{
	class Tile : public GameObject
	{
	public:
		Tile();
		~Tile();

		void InitializeTile(Vector3 index);
		void SetIndex(Vector3 index);

		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		Vector3 GetIndex() { return mIndex; }

	private:
		Vector3 mIndex;
	};
}