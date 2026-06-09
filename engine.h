#pragma once
#include "platform.h"

struct Engine
{
	int				is_running;
	PlatformWindow* platform_window;
	PlatformApi		platform_api;
	MemoryChunk		engine_memory;
	Arena			arena_perm;
	Arena			arena_assets;
};

void
engine_init(Engine* engine);

void
engine_update_frame();

void
engine_destroy();

void
engine_reset();
