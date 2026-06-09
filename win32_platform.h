#pragma once

#include <Windows.h>
#include "util.h"
#include "arena.h"
#include "platform.h"

struct PlatformWindow
{
	HWND	handle;
	LPCWSTR	class_name;
};

PlatformWindow*
win32_create_window(Arena* arena);

int 
win32_pump_messages();

int
win32_show_window(PlatformWindow* window);

MemoryChunk
win32_init_memory(size_t size);

int
win32_destroy_memory(MemoryChunk* mem);
