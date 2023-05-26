#pragma once
#include "bEngine.h"
#include "bGraphicDevice_DX11.h"

namespace b
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }

	private:
		bool mbInitialize = false;

		// unique_ptr : 오로지 한개의 객체만 만들 수 있는 스마트 포인터
		// 특정 객체에 유일한 소유권을 부여하는 포인터 객체
		// 복사나 대입이 불가능함
		std::unique_ptr<b::graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
	};
}

