#pragma once
#include "bGameObject.h"

namespace b
{
	class Door : public GameObject
	{
	public:
		enum class eDoorType
		{
			Item,
			Gold,
			Skul,
			Boss,
			BossLobby,
			MiddleBoss,
			Shop,
			None,
		};

		Door();
		~Door();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetDoorType(eDoorType type) { mType = type; }

	private:
		eDoorType mType;
	};
}

