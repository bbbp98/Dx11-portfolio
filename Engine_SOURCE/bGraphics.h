#pragma once
#include <wrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "bEnums.h"
#include "bMath.h"

#define LOAD_TEXTURE(texture, name, path) \
	texture = Resources::Load<Texture>(name, path)

#define SET_MATERIAL(material, shader, texture) \
	material->SetShader(shader) ;	material->SetTexture(texture)

#define INSERT_MATERIAL(material, name) \
	Resources::Insert(name, material)

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name // alignas(type) : type으로 값 조정

#define CBSLOT_TRANSFORM		0
//#define CBSLOT_PARTICLE		1
#define CBSLOT_GRID			2

namespace b::graphics
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		End
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		End
	};

	enum class eSamplerType
	{
		Point,
		Anisotropic,
		End,
	};

	enum class eRasterizerStateType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};

	enum class eDepthStencilStateType
	{
		Less,
		Greater,
		NoWrite,
		None,
		End,
	};

	enum class eBlendStateType
	{
		Default,
		AlphaBlend,
		OneOne,
		End,
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		End,
	};

	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		float radius;
		float duration;
		float time;
	};
}