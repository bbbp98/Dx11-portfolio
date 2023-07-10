#include "bTile.h"

namespace b
{
	Tile::Tile()
		: mIndex(Vector3::Zero)
	{
	}

	Tile::~Tile()
	{
	}

	void Tile::InitializeTile(Vector3 index)
	{
		mIndex = index;

	}

	void Tile::SetIndex(Vector3 index)
	{
	}

	void Tile::Update()
	{
	}

	void Tile::LateUpdate()
	{
	}

	void Tile::Render()
	{
	}
}