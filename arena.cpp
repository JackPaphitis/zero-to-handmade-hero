#include "arena.h"

void
init_arena(Arena* arena, u8* begin, size_t size)
{
	arena->begin = begin;
	arena->offset = 0;
	arena->capacity = size;
}

void*
arena_malloc_align(Arena* arena, size_t bytes, size_t alignment)
{
	if (!IS_POW2(alignment))
	{
		return 0;
	}

	uintptr_t current = (uintptr_t)arena->begin + arena->offset;
	uintptr_t align = ALIGN(current, alignment);
	size_t newoffset = (align - (uintptr_t)arena->begin) + bytes;

	if (newoffset > arena->capacity)
	{
		// TODO is this what we want to return here?
		return 0;
	}

	arena->offset = newoffset;
	return (void*)align;
}

void
arena_reset(Arena* arena)
{
	arena->offset = 0;
}


