#include "win32_platform.h"

int
CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nShowCmd)
{
	const LPCWSTR CLASS_NAME= L"Test window name";
	
	PlatformWindow* platform_window 
		= win32_create_window(CLASS_NAME, hInstance);

	ShowWindow(platform_window->handle, nShowCmd);

	return 0;
}
