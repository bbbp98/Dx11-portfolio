#pragma once
#include "bGraphics.h"
#include "bResource.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif
namespace b::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(eShaderStage stage, UINT startSlot);

		float GetWidth() { return mImage.GetImages()->width; }
		float GetHeight() { return mImage.GetImages()->height; }

		void Clear();

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};

}
