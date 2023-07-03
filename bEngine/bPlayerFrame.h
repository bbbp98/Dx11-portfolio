#pragma once
#include "bGameObject.h"

namespace b
{
	class PlayerFrame : public GameObject
	{
	public:
		PlayerFrame();
		~PlayerFrame();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

