#pragma once

#include <Windows.h>
#include "util.h"
#include "arena.h"
#include "platform.h"

struct PlatformWindow
{
	HWND handle;
	LPCWSTR class_name;
};

LRESULT CALLBACK 
win32_window_proc(
		HWND hwnd, 
		UINT message, 
		WPARAM wParam,
		LPARAM lParam);

PlatformWindow*
win32_create_window(Arena* arena);

// TODO pump message could take in a window, to pump specific windows message?
int 
win32_pump_messages();

MemoryChunk
win32_init_memory(size_t size);

int
win32_destroy_memory(MemoryChunk* mem);
