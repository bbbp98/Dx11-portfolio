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
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	//extern Vertex rVertexes[];
	//extern ID3D11InputLayout* rectLayout;
	//extern ID3D11Buffer* rectBuffer;
	//extern ID3DBlob* rectVSBlob;
	//extern ID3D11VertexShader* rectVSShader;
	//extern ID3DBlob* rectPSBlob;
	//extern ID3D11PixelShader* rectPSShader;

	void Initialize();
}