#include "engine.h"

static Engine* g_engine = 0;

void
init_engine(Engine* engine)
{
	MemoryChunk engine_memory = engine->platform_api->init_memory(GB(2));
	engine->engine_memory = engine_memory;

	init_arena(	&engine->arena_perm, 
				engine->engine_memory.begin, 
				engine->engine_memory.size/2);
	
	init_arena(	&engine->arena_assets, 
				engine->engine_memory.begin + engine->engine_memory.size/2, 
				engine->engine_memory.size/2);

	PlatformWindow* window = engine->platform_api->create_window(&engine->arena_perm);
	engine->platform_window = window;
}

