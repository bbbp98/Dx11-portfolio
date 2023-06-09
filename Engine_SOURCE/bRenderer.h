#pragma once
#include "bEngine.h"
#include "bGraphicDevice_DX11.h"
#include "bMesh.h"
#include "bShader.h"
#include "bConstantBuffer.h"
#include "bCamera.h"

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

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
		Vector4 mStartUV;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};
	
	extern ConstantBuffer* constantBuffers[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern b::Camera* mainCamera;
	extern std::vector<b::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshes;

	void Initialize();
	void Render();
	void Release();

	void PushDebugmeshAttribute(DebugMesh mesh);
}