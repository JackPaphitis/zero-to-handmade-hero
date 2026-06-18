#include "engine.h"

#define MAX_ENGINE_MEMORY GB(2)

void
engine_init(Engine* engine)
{
	Arena* arena_perm	= &engine->arena_perm;
	Arena* arena_assets	= &engine->arena_assets;

	engine->total_memory	= engine->platform_api.init_memory(MAX_ENGINE_MEMORY);
	
	MemoryChunk perm_mem = 
	{
		engine->total_memory.begin,
		engine->total_memory.capacity/2
	};

	MemoryChunk asset_mem = 
	{
		engine->total_memory.begin + engine->total_memory.capacity/2,
		engine->total_memory.capacity/2
	};

	arena_init(arena_perm, perm_mem); 
	arena_init(arena_assets, asset_mem); 

	PlatformWindow* window  = engine->platform_api.create_window(&engine->arena_perm);
	engine->platform_window = window;
	engine->is_running		= 1;
}

void
engine_update_frame(Engine* engine)
{
	engine->is_running = engine->platform_api.pump_messages();	
}

void
engine_destroy(Engine* engine)
{
	engine->platform_api.destroy_window(engine->platform_window);
	engine->platform_api.destroy_memory(&engine->total_memory);
}

