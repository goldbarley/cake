#include <string.h>

#include "cake/cake.h"
#include "internal.h"
#include "table.h"

table_t *_freetable = NULL;

char *cc = NULL;
char *projname = NULL;

static inline
int _copy_str(char *dst, const char *src)
{
	size_t n = strlen(src);
	dst = malloc(++n);
	if (!dst)
		return RET_ERR;
	dst[n] = '\0';

	return RET_OK;
}

void bake(void)
{

}

int set_cc(const char *s)
{
	return _copy_str(cc, s);
}

int set_projname(const char *s)
{
	return _copy_str(projname, s);
}

int main(void)
{
	/* Test run. */
	if (!)

	return RET_OK
}
