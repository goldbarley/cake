#ifndef CAKE_BUFFER_FIFO_H_
#define CAKE_BUFFER_FIFO_H_ 1

#include "cake/cake.h"

typedef struct buffer
{
	size_t head;
	size_t tail;
	size_t cap;
	size_t size;
	void **datav;
	buffer_type_t type;
} buffer_t;

int add_elem_fifo(buffer_t *restrict buffer, void *restrict data);
int rmv_elem_fifo(buffer_t *restrict buffer, void **restrict retval);
int peek_fifo(buffer_t *restrict buffer, void **restrict retval);
int full_fifo(buffer_t *buffer);
int empty_fifo(buffer_t *buffer);
int size_fifo(buffer_t *restrict buffer, size_t *restrict retval);

#endif /* CAKE_BUFFER_FIFO_H_ */
