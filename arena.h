#pragma once
#include "util.h"

#define DEFAULT_ALIGNMENT (sizeof(void*))
#define IS_POW2(x) ((x) != 0 && (((x) & (x-1)) == 0)) 
#define ALIGN(n,p) (((uintptr_t)(n) + ((uintptr_t)(p)-1)) & (~((uintptr_t)(p)-1)))

struct Arena
{
	u8*		begin;
	size_t	offset; 
	size_t	capacity;
};

void
arena_init(Arena* arena, u8* begin, size_t size);

void*
arena_push(Arena* arena, size_t bytes, size_t alignment);

void
arena_reset(Arena* arena);

void 
arena_pop(Arena* arena, size_t bytes);

