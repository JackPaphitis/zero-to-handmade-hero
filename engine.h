#pragma once
#include "platform.h"

struct Engine
{
	int				is_running;
	PlatformWindow* platform_window;
	PlatformApi		platform_api;
	MemoryChunk		total_memory;
	Arena			arena_perm;
	Arena			arena_assets;
};

void
engine_init(Engine* engine);

void
engine_update_frame(Engine* engine);

void
engine_destroy(Engine* engine);

