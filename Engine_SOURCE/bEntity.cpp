#include "bEntity.h"

namespace b
{
	Entity::Entity()
		: mName(L"")
		, mID((UINT64)this)
	{
	}

	Entity::~Entity()
	{
	}
}