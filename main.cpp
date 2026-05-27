#include "engine.h"
#include "win32_platform.h"
#include "arena.h"
#include "util.h"

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
		win32_init_memory,
		win32_destroy_memory,
	};

	MemoryChunk mem = platform_api.init_memory(GB(1));

	Arena engine_memory = {0};
	init_arena(&engine_memory, mem.begin, mem.size/2);
	
	Engine engine = init_engine(&platform_api, &engine_memory);

	if (engine.platform_window != 0)
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
