#ifndef CAKE_INTERNAL_H_
#define CAKE_INTERNAL_H_ 1

#include <stdbool.h>

#include "cake/cake.h"

typedef struct context
{
	char *cc;
	char *projname;
} context_t;

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

#endif /* CAKE_INTERNAL_H_ */
