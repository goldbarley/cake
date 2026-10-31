#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "cake/cake.h"
#include "mall.h"

/*
 * These were necessary, I just need some
 * placeholder names.
 *
 * They are later defined with macros
 * to make them sensible.
 */
typedef struct _some_bullshit_data
{
	void *addr;
	void *prev;
	void *next;
	bool vacant;
} _very_cool_typedef;

/*
 * These can easily be undefined.
 * So, keep these here.
 *
 * I wish C had namespaces :(
 */
#define _LISTNODE _very_cool_typedef
#define _LIST _very_cool_typedef *

static _Thread_local _LIST _mall[MALL_BLOCK_COUNT] = {0};

#define _IN_RANGE_EI(b, a, c) (a > b && a <= c)

static inline
mallblkszi_t _get_mallblkszi(size_t size)
{
	if (_IN_RANGE_EI(0, size, 16))
		return MALL_BLOCK_SIZE_IDX_16;
	else if (_IN_RANGE_EI(16, size, 64))
		return MALL_BLOCK_SIZE_IDX_64;
	else if (_IN_RANGE_EI(64, size, 128))
		return MALL_BLOCK_SIZE_IDX_128;
	else if (_IN_RANGE_EI(128, size, 256))
		return MALL_BLOCK_SIZE_IDX_256;
	else if (_IN_RANGE_EI(256, size, 512))
		return MALL_BLOCK_SIZE_IDX_512;
	else if (_IN_RANGE_EI(512, size, 1024))
		return MALL_BLOCK_SIZE_IDX_1024;
	else if (_IN_RANGE_EI(1024, size, 2048))
		return MALL_BLOCK_SIZE_IDX_2048;
	else if (_IN_RANGE_EI(2048, size, 4096))
		return MALL_BLOCK_SIZE_IDX_4096;

	return MALL_BLOCK_SIZE_IDX_UNFIT;
}

void *mall(size_t size, void *arg)
{
	/*
	 * Keep the DISCARDs. Otherwise
	 * compiler will give warnings.
	 */
	DISCARD(arg);

	mallblkszi_t idx = _get_mallblkszi(size);

	_LISTNODE *node = malloc(sizeof(_LISTNODE) + size);
	if (!node)
		return NULL;

	node->addr = (void *)(node + 1);
	node->vacant = false;

	/* Assign next and prev pointers */

	return node->addr;
}

void freemall(void *mem, void *arg)
{
	DISCARD(arg);


	/*
	 * This function assumes that 'mem' is always returned
	 * by mall (above).
	 *
	 * Don't pass random stupid pointers in here. Otherwise
	 * it will segfault.
	 */
	((_LISTNODE *) mem - 1)->vacant = true;
}

void *remall(void *orig, size_t size, void *arg)
{
	/*
	 * TODO: Implement.
	 *
	 * The list indices may need to be changed here.
	 * So, the nodes need to be updated accordingly.
	 */

	DISCARD(arg);

	return NULL;
}
