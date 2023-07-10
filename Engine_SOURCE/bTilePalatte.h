#pragma once
#include "bTile.h"

namespace b
{
	union TileID
	{
		struct
		{
			UINT32 x;
			UINT32 y;
		};
		UINT64 id;
	};

	class TilePalatte
	{
	public:
		struct TileInfo
		{
			UINT stage;
			UINT chapter;
			UINT num;
		};

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render();

		static void CreateTile();

		static void Save();
		static void Load();

		//static void SetIndex(int stage, int chapter, int num)
		//{ 
		//	mInfo.stage = stage;
		//	mInfo.chapter = chapter;
		//	mInfo.num = num;
		//}

	private:
		static class Mesh* mMesh;
		static class Material* mMaterial;

		static std::unordered_map<UINT64, Tile*> mTiles;
		//static TileInfo mInfo;
	};
}

