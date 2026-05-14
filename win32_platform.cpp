#include "win32_platform.h"

LRESULT CALLBACK 
win32_window_proc(
		HWND hwnd, 
		UINT message, 
		WPARAM wParam,
		LPARAM lParam)
{
	switch (message)
	{
		case WM_SIZE:
		{
			// TODO dealing with resize of window
		} break;
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		} break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;
		default:
		{
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
	return 0;
}

PlatformWindow*
win32_create_window(LPCWSTR class_name)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	PlatformWindow* platform_window
		= (PlatformWindow*)malloc(sizeof(PlatformWindow));
	
	WNDCLASSW wc = {0};
	wc.lpfnWndProc = win32_window_proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = class_name;

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(
			0,
			class_name,
			L"Learning",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	if (hwnd == 0)
	{
		OutputDebugStringW(L"Handle to window is 0");
		return nullptr;	
	}

	platform_window->handle = hwnd;
	platform_window->class_name = class_name;

	return platform_window;
}

int 
win32_pump_messages()
{
	MSG msg = {};
	while(PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
	{
		if(msg.message == WM_QUIT)
		{
			return 0;
		}
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}
















