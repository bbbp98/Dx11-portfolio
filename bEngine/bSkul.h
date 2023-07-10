#pragma once
#include "bGameObject.h"

namespace b
{
	class Skul : public GameObject
	{
	public:
		Skul();
		~Skul();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

