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
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
		void Draw();

	private:
		// 실제 그래픽 카드 하드웨어 객체
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		// dx11에서 직접적으로 디바이스 객체에 접근하지 않고, 이 객체를 이용해 명령을 내린다.
		// 렌더링 명령을 생성하는 디바이스 컨텍스트
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// 최종적으로 그려질 텍스처(도화지)
		// 구조화된 메모리인 텍셀(텍스쳐의 한 점) 데이터를 관리
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// 렌더타겟에 직접 접근하지 않고, 렌더타겟뷰를 통해 접근
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// 깊이 버퍼
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// 깊이 버퍼에 전근할 수 있는 뷰
		// depth stencil test 중에 텍스처 리소스에 접근
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// 더블 버퍼링 작업을 진행해주는 swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	};
}

