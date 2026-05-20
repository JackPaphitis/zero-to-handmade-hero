#include "engine.h"

Engine
init_engine(PlatformApi* platform_api, Arena arena)
{
	const wchar_t* class_name = L"Testing the agnostic window";
	Engine engine = {};
	engine.platform_api = platform_api;

	engine.platform_window 
	 = platform_api->create_window(class_name, arena);

	return engine;
}
