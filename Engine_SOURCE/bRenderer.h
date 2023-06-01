#pragma once
#include "bEngine.h"
#include "bGraphicDevice_DX11.h"

using namespace b::math;

namespace b::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};
	
	extern Vertex vertexes[];
	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer;
	extern ID3D11Buffer* triangleIdxBuffer;
	extern ID3D11Buffer* triangleCSBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	void Initialize();
	void Update();
}