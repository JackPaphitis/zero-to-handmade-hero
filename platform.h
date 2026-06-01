#pragma once
#include "util.h"
#include "arena.h"

struct PlatformWindow;

struct MemoryChunk
{
	u8* begin;
	size_t size;
};

struct PlatformApi
{
	// TODO this is incorrect, this will make a copy of my arena in
	// function and not change the actual arena, pass a pointer
	PlatformWindow* (*create_window)(Arena* arena);
	int (*pump_messages)();
	MemoryChunk (*init_memory)(size_t);
	int (*destroy_memory)(MemoryChunk*);
};
