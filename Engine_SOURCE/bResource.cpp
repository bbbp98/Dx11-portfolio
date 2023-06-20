#include "bResource.h"

namespace b
{
	Resource::Resource(enums::eResourceType type)
		: mType(type)
		, mKey{}
		, mPath{}
	{
	}

	Resource::~Resource()
	{
	}
}