#pragma once
#include "bEngine.h"
#include "bGraphicDevice_DX11.h"
#include "bMesh.h"
#include "bShader.h"
#include "bConstantBuffer.h"

using namespace b::math;

namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};
	
	extern Vertex vertexes[];
	extern b::Mesh* mesh;
	extern b::Shader* shader;
	extern b::graphics::ConstantBuffer* constantBuffer;

	void Initialize();
	void Release();
}