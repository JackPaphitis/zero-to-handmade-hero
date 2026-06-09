#include "engine.h"
#include "win32_platform.h"

int CALLBACK
WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nShowCmd)
{
	Engine game_engine = {0};

	// bootstrap
	game_engine.platform_api.create_window	= win32_create_window;
	game_engine.platform_api.pump_messages	= win32_pump_messages;
	game_engine.platform_api.init_memory	= win32_init_memory;
	game_engine.platform_api.destroy_memory = win32_destroy_memory;

	engine_init(&game_engine);

	engine_reset();

	while(game_engine.is_running)
	{
		engine_update_frame();
	}
	
	engine_destroy();

	return 0;
}
