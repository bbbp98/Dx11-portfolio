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
		// ComPtr : COM 객체를 위한 스마트 포인터
		// 범위를 벗어난 ComPtr 인스턴스는 해당 COM 객체를 자동으로 Release 시켜줌
		
		// COM(Component Object Model) : 어떤 프로그램이나 시스템을 이루는 컴포넌트들이 상호 통신할 수 있도록 하는 매커니즘
		// new나 delete로 생성, 삭제할 수 없음
		
		// 실제 그래픽 카드 하드웨어 객체
		// 리소스를 만들고 디스플레이 어댑터의 기능을 열거하는데 사용
		// 기능 지원 점검과 자원 할당에 사용
		// 일반적으로 하나의 디바이스만 만듦
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		// dx11에서 직접적으로 디바이스 객체에 접근하지 않고, 이 객체를 이용해 명령을 내린다.
		// 렌더링 명령을 생성하는 디바이스 컨텍스트
		// 렌더 대상을 설정하고, 자원을 그래픽 파이프라인에 묶고, GPU가 수행할 렌더링 명령들을 지시
		// Immediate Context과 Deferred Context로 나눠서 구현
		// Immediate Context : 디바이스에 직접 렌더링. 각 디바이스에는 GPU에서 데이터를 검색할 수 있는 하나의 컨텍스트만 존재한다.
		// Deferred Context : 명력 목록에 GPU 명령을 기록, 주로 다중 스레딩에 사용되며 단일 스레드 애플리케이션에는 필요하지 않음.
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

		D3D11_VIEWPORT mViewPort;
	};

	inline GraphicDevice_DX11*& GetDevice()
	{
		static GraphicDevice_DX11* device = nullptr;
		return device;
	}
}

