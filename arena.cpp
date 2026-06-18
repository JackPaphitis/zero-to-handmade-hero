#include "arena.h"

void
arena_init(	
		Arena*		arena, 
		MemoryChunk	mem)
{
	arena->mem			= mem;
	arena->offset		= 0;
}

void*
arena_push(
		Arena* arena, 
		size_t bytes, 
		size_t alignment)
{
	ASSERT(IS_POW2(alignment))

	uintptr_t current	= (uintptr_t)arena->mem.begin + arena->offset;
	uintptr_t align		= ALIGN(current, alignment);
	size_t newoffset	= (align - (uintptr_t)arena->mem.begin) + bytes;

	if (newoffset > arena->mem.capacity)
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

size_t
arena_save(Arena* arena)
{
	return arena->offset;
}

void 
arena_restore(
		Arena* arena, 
		size_t restore_point)
{
	if (restore_point <= arena->offset)
	{
		arena->offset = restore_point;
	}
}



