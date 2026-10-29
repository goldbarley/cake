#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cake.h"

#define _BUFFER_SPACE (64U)
#define _NULLCHAR_BUFFER_SPACE (66U)

_Bool find_cmd(const char *cmd)
{
	if (!cmd)
		return false;

	if (strchr(cmd, '/') && access(cmd, X_OK) == 0)
	{
		fprintf(stdout, "Found %s\n", cmd);
		return true;
	}

	char *_path = getenv("PATH");
	if (!_path)
	{
		fputs("Error: Could not get environment variable: PATH.\n",
		      stderr);
		return false;
	}

	const size_t npath = strlen(_path);
	const size_t nbuf = npath + _BUFFER_SPACE;

	char *memblk = (char *) malloc((npath << 1) + _NULLCHAR_BUFFER_SPACE);
	if (!memblk)
	{
		fputs("Error: Memory allocation failed.\n", stderr);
		return false;
	}

	char *memblk2 = memcpy(memblk, _path, npath);
	memblk2[npath] = 0;

	char *path = memblk + npath;

	char *tok = strtok(memblk, ":");
	while (tok)
	{
		snprintf(path, nbuf, "%s/%s", tok, cmd);

		if (access(path, X_OK) == 0)
		{
			fprintf(stdout, "Found %s\n", path);
			free(memblk);
			return true;
		}
		tok = strtok(NULL, ":");
	}

	free(memblk);
	return false;
}
