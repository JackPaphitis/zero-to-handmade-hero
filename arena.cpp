#include "arena.h"

void
arena_init(	
		Arena*	arena, 
		u8*		begin, 
		size_t	size)
{
	arena->begin = begin;
	arena->offset = 0;
	arena->capacity = size;
}

void*
arena_push(
		Arena* arena, 
		size_t bytes, 
		size_t alignment)
{
	ASSERT(IS_POW2(alignment))

	uintptr_t current	= (uintptr_t)arena->begin + arena->offset;
	uintptr_t align		= ALIGN(current, alignment);
	size_t newoffset	= (align - (uintptr_t)arena->begin) + bytes;

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

void 
arena_pop(Arena* arena, size_t bytes)
{
	// TODO(jack): this seems bad, we dont want 
	// to pop off a stack that aligned.
	// how do we know we popped correctly
	// we should add save points and pop back to save
	if (bytes > arena->offset)
	{
		arena->offset = 0;
	}
	else
	{
		arena->offset -= bytes;
	}
}



