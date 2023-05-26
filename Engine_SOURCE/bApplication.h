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

		// unique_ptr : ������ �Ѱ��� ��ü�� ���� �� �ִ� ����Ʈ ������
		// Ư�� ��ü�� ������ �������� �ο��ϴ� ������ ��ü
		// ���糪 ������ �Ұ�����
		std::unique_ptr<b::graphics::GraphicDevice_DX11> graphicDevice;

		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
	};
}

