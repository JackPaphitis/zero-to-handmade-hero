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
	Engine game_engine = {0};
	PlatformApi platform_api = {0};
	platform_api.create_window = win32_create_window;
	platform_api.pump_messages = win32_pump_messages;
	platform_api.init_memory = win32_init_memory;
	platform_api.destroy_memory = win32_destroy_memory;
	game_engine.platform_api = &platform_api;
	
	init_engine(&game_engine);

	// TODO window code, take out to show_window platform_api?
	ShowWindow(game_engine.platform_window->handle, nShowCmd);

	while(game_engine.platform_api->pump_messages())
	{

	}

	return 0;
}
