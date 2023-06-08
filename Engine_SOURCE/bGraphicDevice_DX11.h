#pragma once
#include "bEngine.h"
#include "bGraphics.h"

namespace b::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CompileFromFile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);
		bool CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader);


		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		void BindVertexBuffer(UINT startSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT offset);
		void BindVertexShader(ID3D11VertexShader* pVertexShader);
		void BindPixelShader(ID3D11PixelShader* pPixelShader);

		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void BindsConstantBuffer(eCBType type, ID3D11Buffer* buffer);

		void BindViewPort(D3D11_VIEWPORT* viewPort);

		void Draw();

	private:
		// �������� ����
		// 1. �������� �������� -> ����ϱⰡ ��ƴ�
		// 2. �߰��� ������ ���� �ٲٰų� �ϸ� ���α׷��� ������ ���� �� �ִ�. -> �����ؼ� ����ؾ� �Ѵ�.
		// 3. �޸� ������ ���α׷��Ӱ� ���� ����� �Ѵ�. -> �߸� ����ϰ� �Ǹ� �޸� ������ �����. ������ �ʹ� ���� ����� ���α׷��� ������.
		// 
		// C++������ �޸� �����κ��� �������� �����ϱ� ���ؼ� ����Ʈ �����Ͷ�� ����� �����ϰ� �ִ�.
		// ����Ʈ �����ʹ� ������ó�� �����ϴ� ���ø� Ŭ���� ��ü�̰�, ������� �ʴ� �޸𸮸� �ڵ����� �������ش�.
		// #include <memory>
		// std::unique_ptr<> : ���� �ϳ��� ��ü�� ������ �� �ֵ��� ���� ����Ʈ ������
		// std::shared_ptr<> : �ϳ��� Ư�� ��ü�� �����ϴ� ����Ʈ �����Ͱ� �� �� �������� üũ�ϴ� ����Ʈ ������
		// std::weak_ptr<> : shared_ptr�� ���� Ƚ���� ������� �����ϱ� ������ 
		// ���� ���ΰ� ���θ� ����Ű�� shared_ptr�̶�� ���� Ƚ���� ���� 0�� ���� �����Ƿ� ������ �޸𸮰� �������� �ʴ´�.
		// ComPtr : COM ��ü�� ���� ����Ʈ ������
		// ������ ��� ComPtr �ν��Ͻ��� �ش� COM ��ü�� �ڵ����� Release ������
		
		// COM(Component Object Model) : � ���α׷��̳� �ý����� �̷�� ������Ʈ���� ��ȣ ����� �� �ֵ��� �ϴ� ��Ŀ����
		// new�� delete�� ����, ������ �� ����
		
		// ���� �׷��� ī�� �ϵ���� ��ü
		// ���ҽ��� ����� ���÷��� ������� ����� �����ϴµ� ���
		// ��� ���� ���˰� �ڿ� �Ҵ翡 ���
		// �Ϲ������� �ϳ��� ����̽��� ����
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		// dx11���� ���������� ����̽� ��ü�� �������� �ʰ�, �� ��ü�� �̿��� ����� ������.
		// ������ ����� �����ϴ� ����̽� ���ؽ�Ʈ
		// ���� ����� �����ϰ�, �ڿ��� �׷��� ���������ο� ����, GPU�� ������ ������ ��ɵ��� ����
		// Immediate Context�� Deferred Context�� ������ ����
		// Immediate Context : ����̽��� ���� ������. �� ����̽����� GPU���� �����͸� �˻��� �� �ִ� �ϳ��� ���ؽ�Ʈ�� �����Ѵ�.
		// Deferred Context : ��� ��Ͽ� GPU ����� ���, �ַ� ���� �������� ���Ǹ� ���� ������ ���ø����̼ǿ��� �ʿ����� ����.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// ���������� �׷��� �ؽ�ó(��ȭ��)
		// ����ȭ�� �޸��� �ؼ�(�ؽ����� �� ��) �����͸� ����
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// ����Ÿ�ٿ� ���� �������� �ʰ�, ����Ÿ�ٺ並 ���� ����
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// ���� ����
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// ���� ���ۿ� ������ �� �ִ� ��
		// depth stencil test �߿� �ؽ�ó ���ҽ��� ����
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// ���� ���۸� �۾��� �������ִ� swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;
	};

	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}
}

