#ifndef MEM_ARENA_H_
#define MEM_ARENA_H_ 1

#include <stdbool.h>
#include <stddef.h>

#include "cake/cake.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define MARENA_ALIGNMENT (_Alignof(max_align_t))

struct marena
{
	unsigned char *buffer;
	size_t capacity;
	size_t offset;
	bool uowned;
};

static inline
bool align_up(size_t value, size_t align, size_t *result)
{
	if (!result || !align)
		return false;

	if ((align & (align - 1)))
		return false;

	if (value > SIZE_MAX - (align - 1))
		return false;

	*result = (value + align - 1) & ~(align - 1);
	return true;
}

static inline
int marena_construct(register struct marena *arena, size_t capacity)
{
	if (!arena)
		return RET_ERR;

	arena->buffer = malloc(capacity);
	if (!arena->buffer)
		return RET_ERR;

	arena->capacity = capacity;
	arena->offset = 0;
	arena->uowned = false;

	return RET_OK;
}

/* Either use construct/demolish or set but not both. */
static inline
int marena_set(register struct marena *arena, void *addr,
		      size_t size)
{
	if (!arena || !addr)
		return RET_ERR;

	arena->buffer = addr;
	arena->capacity = size;
	arena->uowned = true;
	arena->offset = 0;

	return RET_OK;
}

static inline
void *marena_alloc(register struct marena *arena, size_t size)
{
	if (!arena || !size)
		return NULL;

	size_t asize = 0;
	if (!align_up(size, MARENA_ALIGNMENT, &asize))
		return NULL;

	if (asize > arena->capacity - arena->offset)
		return NULL;

	void *mem = (void *)(arena->buffer + arena->offset);
	arena->offset += asize;

	return mem;
}

static inline
void *marena_alloc_aligned(register struct marena *arena, size_t size,
			      size_t align)
{
	if (!arena || !size)
		return NULL;

	size_t asize = 0;
	if (!align_up(size, align, &asize))
		return NULL;

	if (asize > arena->capacity - arena->offset)
		return NULL;

	void *mem = (void *)(arena->buffer + arena->offset);
	arena->offset += asize;

	return mem;
}

static inline
size_t marena_save(const struct marena *arena)
{
	return arena ? arena->offset : 0;
}

static inline
void marena_seek(struct marena *arena, size_t offset)
{
	if (arena && offset <= arena->capacity)
		arena->offset = offset;
}

static inline
void marena_clear(struct marena *arena)
{
	if (!arena)
		return;

	arena->offset = 0;
}

static inline
void marena_demolish(struct marena *arena)
{
	if (!arena)
		return;

	if (!arena->uowned && arena->buffer)
		free(arena->buffer);
	arena->buffer = NULL;
	arena->capacity = 0;
	arena->offset = 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MEM_ARENA_H_ */
