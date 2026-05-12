#include "win32_platform.h"

LRESULT CALLBACK 
win32_window_proc(
		HWND hwnd, 
		UINT message, 
		WPARAM wParam,
		LPARAM lParam)
{
	return DefWindowProc(hwnd,message, wParam, lParam);
}

PlatformWindow*
win32_create_window(
		LPCWSTR class_name,
		HINSTANCE hInstance)
{
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
		return nullptr;	
	}

	platform_window->handle = hwnd;
	platform_window->class_name = class_name;

	return platform_window;
}
