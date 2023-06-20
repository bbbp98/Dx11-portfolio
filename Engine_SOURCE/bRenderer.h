#pragma once
#include "bEngine.h"
#include "bGraphicDevice_DX11.h"
#include "bMesh.h"
#include "bShader.h"
#include "bConstantBuffer.h"

using namespace b::math;
using namespace b::graphics;

namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};
	
	extern Vertex vertexes[];
	extern ConstantBuffer* constantBuffers[(UINT)eCBType::End];

	void Initialize();
	void Release();
}