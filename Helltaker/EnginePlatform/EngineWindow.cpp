#include "EngineWindow.h"
#include <EngineBase\EngineDebug.h>
#include "WindowImage.h"

bool UEngineWindow::WindowLive = true;
HINSTANCE UEngineWindow::hInstance;


LRESULT CALLBACK UEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		WindowLive = false;
		// PostQuitMessage(123213);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void UEngineWindow::Init(HINSTANCE _hInst)
{
	hInstance = _hInst;
}


UEngineWindow::UEngineWindow()
{}

UEngineWindow::~UEngineWindow()
{
	if (nullptr != WindowImage)
	{
		delete WindowImage;
		WindowImage = nullptr;
	}

}

void UEngineWindow::Open(std::string_view _Title /*= "Title"*/)
{
	// 간혹가다가 앞쪽이이나 뒤쪽에 W가 붙거나 A가 붙어있는 함수들을 보게 될겁니다.
	// A가 붙어있으면 멀티바이트 함수
	// W가 붙어있으면 와이드 바이트 함수
	WNDCLASSEXA wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "DefaultWindow";
	wcex.hIconSm = nullptr;

	RegisterClassExA(&wcex);

	// const std::string& = 내부에 뭘들고 있다고 생각하라고 했나요?
	// std::vector<char> 들고 있다고 생각하라고 했다.
	// _Title[0] = char&를 리턴해준 것과 같다.
	// _Title.c_str(); => 자연스럽게 내부에서 
	// const char* Test = &_Title[0]
	// return Test;

	hWnd = CreateWindowA("DefaultWindow", _Title.data(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		MsgBoxAssert("윈도우 생성에 실패했습니다.");
		return;
	}

	HDC hDC = GetDC(hWnd);

	if (nullptr == WindowImage)
	{
		WindowImage = new UWindowImage();
		WindowImage->Create(hDC);
	}


	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

}

unsigned __int64 UEngineWindow::WindowMessageLoop(void(*_Update)(), void(*_End)())
{
	MSG msg = {};

	while (WindowLive)
	{
		// 기본 메시지 루프입니다:
		// 10개가 들어있을 
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 메세지 루프의 데드타임이라는 곳에서 실행됩니다.
		if (nullptr != _Update)
		{
			_Update();
		}
	}

	if (nullptr != _End)
	{
		_End();
	}

	return msg.wParam;
}


