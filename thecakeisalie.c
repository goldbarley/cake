#include <stdio.h>
#include <string.h>

#include <cake/cake.h>

/*
 * Building Cake with Cake.
 */
int main(void)
{
	static char russtrbuf[4096U] = {0};

	context_t *ctx;
	get_context(&ctx);
	check_ret(set_cc(ctx, "cc"), NULL, NULL, "Could not set C compiler\n");
	const char *cc = get_cc(ctx);
	fprintf(stdout, "Set C compiler to %s\n", cc);

	check_ret(set_projname(ctx, "cake"), NULL, NULL, "Could not set project name\n");
	const char *projname = get_projname(ctx);
	fprintf(stdout, "Set project name to %s\n", projname);

	check_ret(find_cmd(cc), NULL, NULL, "Could not find %s\n", cc);
	fprintf(stdout, "Found %s\n", cc);

	cmdarg_t argv[64U];
	const char *cflags[64U] = {
		__FILE__, "-Wall", "-O3", "-DNDEBUG", "-o",
		projname
	};

	add_cmdargs(cflags, argv, 6);

	done(ctx);

	return RET_OK;
}
