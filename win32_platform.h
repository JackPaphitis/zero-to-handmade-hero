#pragma once

#include <Windows.h>
#include "platform.h"

struct PlatformWindow
{
	HWND	handle;
	LPCWSTR	class_name;
	HDC		dc;
};

PlatformWindow*
win32_create_window(Arena* arena);

void
win32_destroy_window(PlatformWindow* window);

int 
win32_pump_messages();

MemoryChunk
win32_init_memory(size_t capacity);

int
win32_destroy_memory(MemoryChunk* mem);

FileData*
win32_read_file(const wchar_t* path, Arena* arena);

int
win32_write_file(const wchar_t* path, FileData* file_data);
