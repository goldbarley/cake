#include <stdio.h>
#include <string.h>

#include "cake/cake.h"
#include "internal.h"

char *cc = NULL;
char *projname = NULL;

static inline
int _copy_str(char **restrict dst, const char *restrict src)
{
	size_t n = strlen(src);
	char *p = malloc(++n);
	if (!p)
		return RET_ERR;

	memcpy(p, src, n);

	*dst = p;

	return RET_OK;
}

static inline
void _free_null(void **ptr)
{
	if (!ptr)
		return;
	free(*ptr);
	*ptr = NULL;
}

int set_cc(const char *s)
{
	return _copy_str(&cc, s);
}

int set_projname(const char *s)
{
	return _copy_str(&projname, s);
}

void done(void)
{
	_free_null((void **) &cc);
	_free_null((void **) &projname);
}

int main(void)
{
	/* Test run. */
	set_cc("cc");
	set_projname("valkyrie");

	fprintf(stdout, "%s %s\n", cc, projname);

	done();

	return RET_OK;
}
