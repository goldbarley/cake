#ifndef CAKE_TABLE_H_
#define CAKE_TABLE_H_ 1

#include <stddef.h>

typedef unsigned int index_t;

typedef struct tableitem
{
	int key;
	void *addr;
	struct hashnode *next;
} tableitem_t;

typedef struct table
{
	tableitem_t **list;
	size_t size;
} table_t;

static inline
index_t get_index(int key, size_t size)
{
	/* Implement. */
}

int create_table(table_t **table);
int delete_table(table_t *table);

#endif /* CAKE_TABLE_H_ */
