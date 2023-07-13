#include "bShader.h"
#include "bRenderer.h"

namespace b
{
	Shader::Shader()
		: Resource(b::enums::eResourceType::Shader)
		, mInputLayout(nullptr)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, mRSType(eRasterizerStateType::SolidBack)
		, mDSType(eDepthStencilStateType::Less)
		, mBSType(eBlendStateType::AlphaBlend)
	{
	}

	Shader::~Shader()
	{
		mInputLayout->Release();
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool Shader::Create(const eShaderStage stage
		, const std::wstring& fileName, const std::string& funcName)
	{
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += fileName;

		ID3DBlob* errorBlob = nullptr;

		if (stage == eShaderStage::VS)
		{
			GetDevice()->CompileFromFile(fullPath, funcName, "vs_5_0", mVSBlob.GetAddressOf());
			GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize(), mVS.GetAddressOf());
		}
		else if (stage == eShaderStage::PS)
		{
			GetDevice()->CompileFromFile(fullPath, funcName, "ps_5_0", mPSBlob.GetAddressOf());
			GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer(), mPSBlob->GetBufferSize(), mPS.GetAddressOf());
		}

		return true;
	}

	void Shader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(mTopology);
		GetDevice()->BindInputLayout(mInputLayout);

		GetDevice()->BindVertexShader(mVS.Get());
		GetDevice()->BindPixelShader(mPS.Get());


		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rsState = renderer::rasterizerStates[(UINT)mRSType];
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)mDSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> bsState = renderer::blendStates[(UINT)mBSType];

		GetDevice()->BindRasterizerState(rsState.Get());
		//GetDevice()->BindDepthStencilState(dsState.Get());
		GetDevice()->BindBlendState(bsState.Get());
	}
}