#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "cake/cake.h"
#include "internal.h"

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

CAKE_FORMAT_PRINTF(4, 5)
void check_ret(int ret, callback_t errcb, void* arg, const char *msg, ...)
{
	if (!msg)
		if (ret != RET_OK && errcb)
			errcb(arg);

	if (ret == RET_OK)
		return;

	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);

	if (errcb)
		errcb(arg);
}

int get_context(context_t **ctx)
{
	if (!ctx)
		return RET_ERR;

	*ctx = NULL;
	context_t *_ctx = malloc(sizeof(struct context));
	if (!_ctx)
		return RET_ERR;

	*ctx = _ctx;

	return RET_OK;
}

int set_cc(context_t *restrict ctx, const char *restrict s)
{
	return _copy_str(&ctx->cc, s);
}

int set_projname(context_t *restrict ctx, const char *restrict s)
{
	return _copy_str(&ctx->projname, s);
}

const char *get_cc(context_t *ctx)
{
	return ctx->cc;
}

const char *get_projname(context_t *ctx)
{
	return ctx->projname;
}

int add_cmdargs(const char **args, cmdarg_t *argv, size_t argc)
{
	if (!args || !argv)
		return RET_ERR;

	for (size_t i = 0; i < argc; ++i)
	{
		/*
		 * const char * is casted to char * here.
		 * This will cause problems.
		 *
		 * FIXME: Find a solution.
		 */
		argv[i].s = (char *) args[i];
		argv[i].len = strlen(args[i]);
	}

	return RET_OK;
}

void done(context_t *ctx)
{
	_free_null((void **) &ctx->cc);
	_free_null((void **) &ctx->projname);
	_free_null((void **) &ctx);
}
