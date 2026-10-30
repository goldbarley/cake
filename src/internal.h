#ifndef CAKE_INTERNAL_H_
#define CAKE_INTERNAL_H_ 1

#include "cake/cake.h"

typedef struct cmd_buffer
{
	size_t head;
	size_t tail;
	size_t cap;
	size_t size;
} cmd_buffer_t;

#endif /* CAKE_INTERNAL_H_ */
