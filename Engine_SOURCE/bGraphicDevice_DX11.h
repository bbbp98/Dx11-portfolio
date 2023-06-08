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
		// 포인터의 단점
		// 1. 가독성이 떨어진다 -> 사용하기가 어렵다
		// 2. 중간에 포인터 값을 바꾸거나 하면 프로그램이 오류가 생길 수 있다. -> 조심해서 사용해야 한다.
		// 3. 메모리 해제를 프로그래머가 직접 해줘야 한다. -> 잘못 사용하게 되면 메모리 누수가 생긴다. 누수가 너무 많이 생기면 프로그램이 꺼진다.
		// 
		// C++에서는 메모리 누수로부터 안정성을 보장하기 위해서 스마트 포인터라는 기능을 제공하고 있다.
		// 스마트 포인터는 포인터처럼 동작하는 템플릿 클래스 객체이고, 사용하지 않는 메모리를 자동으로 해제해준다.
		// #include <memory>
		// std::unique_ptr<> : 오직 하나의 객체만 소유할 수 있도록 만든 스마트 포인터
		// std::shared_ptr<> : 하나의 특정 객체를 참조하는 스마트 포인터가 총 몇 개인지를 체크하는 스마트 포인터
		// std::weak_ptr<> : shared_ptr은 참조 횟수를 기반으로 동작하기 때문에 
		// 만약 서로가 서로를 가리키는 shared_ptr이라면 참조 횟수가 절대 0이 되지 않으므로 영원히 메모리가 해제되지 않는다.
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

