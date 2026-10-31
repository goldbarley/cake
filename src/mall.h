#ifndef CAKE_MALL_H_
#define CAKE_MALL_H_ 1

#include <stddef.h>

typedef enum mallblkszi
{
	MALL_BLOCK_SIZE_IDX_UNFIT = -0x00000001,
	MALL_BLOCK_SIZE_IDX_16 = 0x00000000,
	MALL_BLOCK_SIZE_IDX_64 = 0x00000001,
	MALL_BLOCK_SIZE_IDX_128 = 0x00000002,
	MALL_BLOCK_SIZE_IDX_256 = 0x00000003,
	MALL_BLOCK_SIZE_IDX_512 = 0x00000004,
	MALL_BLOCK_SIZE_IDX_1024 = 0x00000005,
	MALL_BLOCK_SIZE_IDX_2048 = 0x00000006,
	MALL_BLOCK_SIZE_IDX_4096 = 0x00000007,
	MALL_BLOCK_SIZE_IDX_MAX_ENUM = 0x7FFFFFFF
} mallblkszi_t;

#define MALL_BLOCK_COUNT (8U)

void *mall(size_t size, void *arg);
void freemall(void *mem, void *arg);
void *remall(void *orig, size_t size, void *arg);

#endif /* CAKE_ALLOCLIST_H_ */
