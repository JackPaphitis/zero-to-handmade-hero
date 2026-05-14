#include "engine.h"
#include "win32_platform.h"

// engine
//	renderer (opengl, vulkan)
//	window (win32, linux)

int
CALLBACK
WinMain(HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nShowCmd)
{
	// bootstrap api
	PlatformApi platform_api = 
	{ 
		win32_create_window,
		win32_pump_messages,
	};

	Engine engine = init_engine(&platform_api);

	if (engine.platform_window != nullptr)
	{
		OutputDebugStringW(L"Window");
	}
	else
	{
		OutputDebugStringW(L"NO WINDOW");
	}
	
	ShowWindow(engine.platform_window->handle, nShowCmd);

	while(engine.platform_api->pump_messages())
	{

	}

	return 0;
}
