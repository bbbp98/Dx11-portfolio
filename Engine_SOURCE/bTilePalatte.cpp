#include "bTilePalatte.h"
#include "bResources.h"
#include "bInput.h"
#include "bObject.h"

namespace b
{
	Mesh* TilePalatte::mMesh = nullptr;
	Material* TilePalatte::mMaterial = nullptr;

	std::unordered_map<UINT64, Tile*> TilePalatte::mTiles = {};
	//TileInfo TilePalatte::mInfo = {};

	void TilePalatte::Initialize()
	{
	}

	void TilePalatte::Update()
	{
	}

	void TilePalatte::LateUpdate()
	{
	}

	void TilePalatte::Render()
	{
	}

	void TilePalatte::CreateTile()
	{
		//Vector3 mousePos = Input::GetMousePosToWorld();

		//Tile* tile = object::Instantiate<Tile>(eLayerType::BackGround_Out);
		//tile->InitializeTile();
	}

	void TilePalatte::Save()
	{
	}

	void TilePalatte::Load()
	{
	}
}