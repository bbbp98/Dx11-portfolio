#pragma once
#include "bGameObject.h"

namespace b
{
	class ForestBG : public GameObject
	{
	public:
		ForestBG();
		~ForestBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}

