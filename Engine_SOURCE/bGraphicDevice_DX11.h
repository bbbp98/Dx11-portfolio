#pragma once
#include "bEngine.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace b::graphics
{
	class GraphicDevice_DX11
	{
	public:
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CreateShader();

		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);

		void BindViewPort(D3D11_VIEWPORT* viewPort);

		void Draw();

	private:
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

