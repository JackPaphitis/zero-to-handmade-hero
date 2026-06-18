#pragma once
#include "util.h"

#define DEFAULT_ALIGNMENT (sizeof(void*))
#define IS_POW2(x) ((x) != 0 && (((x) & (x-1)) == 0)) 
#define ALIGN(n,p) (((uintptr_t)(n) + ((uintptr_t)(p)-1)) & (~((uintptr_t)(p)-1)))

struct MemoryChunk
{
	u8*		begin;
	size_t	capacity;
};

struct Arena
{
	MemoryChunk	mem;
	size_t		offset;
};

void
arena_init(Arena* arena, MemoryChunk mem);

void*
arena_push(Arena* arena, size_t bytes, size_t alignment);

void
arena_reset(Arena* arena);

size_t 
arena_save(Arena* arena);

void 
arena_restore(Arena* arena, size_t restore_point);

