#pragma once
#include "platform.h"
#include "arena.h"
#include "util.h"

struct Engine
{
	int is_running;
	PlatformWindow* platform_window;
	PlatformApi* platform_api;
	MemoryChunk engine_memory;
	Arena arena_perm;
	Arena arena_assets;
};

void
init_engine(Engine* engine);

void
restart_engine(Engine* engine);

void
destroy_engine(Engine* engine);
