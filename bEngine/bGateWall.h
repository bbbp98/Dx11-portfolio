#pragma once
#include "bGameObject.h"

namespace b
{
	class GateWall : public GameObject
	{
	public:
		GateWall();
		~GateWall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

