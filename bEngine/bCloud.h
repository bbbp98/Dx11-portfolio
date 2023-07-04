#pragma once
#include "bGameObject.h"

namespace b
{
	class Cloud : public GameObject
	{
	public:
		Cloud();
		~Cloud();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		class MeshRenderer* mMeshRenderer;
	};
}

