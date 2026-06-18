#pragma once
#include "util.h"
#include "arena.h"

struct PlatformWindow;

struct FileData
{
	char*	file_bytes;
	u32		size;
};

struct PlatformApi
{
	PlatformWindow* (*create_window)(Arena* arena);
	void			(*destroy_window)(PlatformWindow*);
	int				(*pump_messages)();
	MemoryChunk		(*init_memory)(size_t);
	int				(*destroy_memory)(MemoryChunk*);
	FileData*		(*read_files)(const wchar_t* path, Arena* arena);
};
