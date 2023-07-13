#include "bToolScene.h"
#include "bApplication.h"
#include "bTilePalatte.h"
#include "bInput.h"

extern b::Application application;

namespace b
{
	ToolScene::ToolScene()
		: mIndex{}
		, mHdc(NULL)
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		mHdc = GetDC(application.GetHwnd());
		Scene::Initialize();
		TilePalatte::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			//Vector3 pos = Input::GetMousePosToWorld();
			Vector2 pos = Input::GetMousePos();
			int w = 0;
		}
	}

	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void ToolScene::Render()
	{
		//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, brush);
		//::Rectangle(mHdc, -1, -1, 201, 201);
		//SelectObject(mHdc, oldBrush);
		//DeleteObject(brush);

		//mHdc = GetDC(application.GetToolHwnd());
		SetBkMode(mHdc, TRANSPARENT);
		SetTextColor(mHdc, RGB(255, 0, 0));
		HFONT hFont = CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, 0);
		SetTextAlign(mHdc, TA_CENTER);
		HFONT oldFont = (HFONT)SelectObject(mHdc, hFont);
		DeleteObject(oldFont);

		std::wstring xs = L"Stage " + std::to_wstring(mIndex[0]);
		LPCWSTR lString = xs.c_str();
		TextOut(mHdc, 100, 30, lString, lstrlen(lString));

		std::wstring ys = L"Chapter " + std::to_wstring(mIndex[1]);
		lString = ys.c_str();
		TextOut(mHdc, 100, 90, lString, lstrlen(lString));

		std::wstring zs = L"Num " + std::to_wstring(mIndex[2]);
		lString = zs.c_str();
		TextOut(mHdc, 100, 150, lString, lstrlen(lString));
		Scene::Render();
	}
}

//LRESULT CALLBACK TileWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_CREATE:
//	{
//		RECT rect = { 0, 0, 200, 200 };
//		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
//
//		SetWindowPos(hWnd
//			, nullptr, 1600, 0
//			, rect.right - rect.left
//			, rect.bottom - rect.top
//			, 0);
//		ShowWindow(hWnd, true);
//	}
//	//case WM_LBUTTONDOWN:
//	//{
//	//	if (GetFocus())
//	//	{
//	//		::POINT mousePos = {};
//	//		::GetCursorPos(&mousePos);
//	//		::ScreenToClient(application.GetToolHwnd(), &mousePos);
//
//	//		if (mousePos.y >= 30 && mousePos.y <= 50)
//	//			mIndex[0]++;
//	//		if (mousePos.y >= 90 && mousePos.y <= 110)
//	//			mIndex[1]++;
//	//		if (mousePos.y >= 150 && mousePos.y <= 170)
//	//			mIndex[2]++;
//
//	//		//message = WM_PAINT;
//	//		//b::TilePalatte::SetIndex(mIndex[0], mIndex[1], mIndex[2]);
//	//	}
//	//}
//	//break;
//	//case WM_RBUTTONDOWN:
//	//{
//	//	if (GetFocus())
//	//	{
//	//		mIndex[0] = 0;
//	//		mIndex[1] = 0;
//	//		mIndex[2] = 0;
//	//	}
//
//	//	message = WM_PAINT;
//	//}
//	//break;
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//
//		/*SetBkMode(hdc, TRANSPARENT);
//		SetTextColor(hdc, RGB(0, 0, 0));
//		HFONT hFont = CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, 0);
//		SetTextAlign(hdc, TA_CENTER);
//		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
//		DeleteObject(oldFont);
//
//		std::wstring xs = L"Stage " + std::to_wstring(mIndex[0]);
//		LPCWSTR lString = xs.c_str();
//		TextOut(hdc, 100, 30, lString, lstrlen(lString));
//
//		std::wstring ys = L"Chapter " + std::to_wstring(mIndex[1]);
//		lString = ys.c_str();
//		TextOut(hdc, 100, 90, lString, lstrlen(lString));
//
//		std::wstring zs = L"Num " + std::to_wstring(mIndex[2]);
//		lString = zs.c_str();
//		TextOut(hdc, 100, 150, lString, lstrlen(lString));*/
//
//		EndPaint(hWnd, &ps);
//	}
//	break;
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		switch (wmId)
//		{
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//	}
//	
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//
//	return 0;
////;}