#include <string.h>

#include "fifo.h"

int add_elem_fifo(buffer_t *restrict buffer, void *restrict data)
{
	if (!buffer || buffer->type != BUFFER_TYPE_FIFO
		|| full_fifo(buffer) == RET_OK)
		return RET_ERR;

	buffer->datav[buffer->head] = data;
	buffer->head = (buffer->head + 1) % buffer->cap;
	++buffer->size;

	return RET_OK;
}

int rmv_elem_fifo(buffer_t *restrict buffer, void **restrict retval)
{
	if (!buffer || buffer->type != BUFFER_TYPE_FIFO
		|| empty_fifo(buffer) == RET_OK || !retval)
		return RET_ERR;

	*retval = buffer->datav[buffer->tail];
	buffer->tail = (buffer->tail + 1) % buffer->cap;
	--buffer->size;

	return RET_OK;
}

int peek_fifo(buffer_t *restrict buffer, void **restrict retval)
{
	if (!buffer || buffer->type != BUFFER_TYPE_FIFO
		|| empty_fifo(buffer) == RET_OK || !retval)
		return RET_ERR;

	*retval = buffer->datav[buffer->tail];

	return RET_OK;
}

int full_fifo(buffer_t *buffer)
{
	if (!buffer || buffer->type != BUFFER_TYPE_FIFO)
		return RET_ERR;

	return (buffer->head + 1) % buffer->cap == buffer->tail ? RET_OK : RET_ERR;
}

int empty_fifo(buffer_t *buffer)
{
	if (!buffer || buffer->type != BUFFER_TYPE_FIFO)
		return RET_ERR;

	return buffer->head == buffer->tail ? RET_OK : RET_ERR;
}

int size_fifo(buffer_t *restrict buffer, size_t *restrict retval)
{
	if (!buffer || buffer->type != BUFFER_TYPE_FIFO)
		return RET_ERR;

	*retval = buffer->size;

	return RET_OK;
}
