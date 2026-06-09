#include "engine.h"

#define MAX_ENGINE_MEMORY GB(2)

static Engine*			g_engine		= 0;
static PlatformApi*		g_platform_api	= 0;

void
engine_init(Engine* engine)
{
	g_engine		= engine;
	g_platform_api	= &engine->platform_api;
	
	Arena* arena_perm	= &engine->arena_perm;
	Arena* arena_assets	= &engine->arena_assets;

	g_engine->engine_memory = g_platform_api->init_memory(MAX_ENGINE_MEMORY);

	arena_init(	arena_perm, 
				engine->engine_memory.begin, 
				engine->engine_memory.size/2);
	
	arena_init(	arena_assets, 
				engine->engine_memory.begin + engine->engine_memory.size/2, 
				engine->engine_memory.size/2);

	PlatformWindow* window  = g_platform_api->create_window(&engine->arena_perm);
	engine->platform_window = window;
	engine->is_running		= 1;
}

void
engine_update_frame()
{
	g_engine->is_running = g_platform_api->pump_messages();	
}

void
engine_destroy()
{
	MemoryChunk* engine_memory = &g_engine->engine_memory;
	
	g_engine->arena_perm	= {0};
	g_engine->arena_assets	= {0};

	g_platform_api->destroy_memory(engine_memory);
}

void
engine_reset()
{
	if (g_engine != 0)
	{
		engine_destroy();
		engine_init(g_engine);
	}
}













