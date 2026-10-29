#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cake.h"

#define _NULLCHAR_BUFFER_SPACE (2U)

_Bool find_cmd(const char *cmd)
{
	if (!cmd)
		return false;

	if (strchr(cmd, '/') && access(cmd, X_OK) == 0)
	{
		fprintf(stdout, "Found %s\n", cmd);
		return true;
	}

	const size_t ncmd = strlen(cmd);
	char *_path = getenv("PATH");
	if (!_path)
	{
		fputs("Error: Could not get environment variable: PATH.\n",
		      stderr);
		return false;
	}

	const size_t npath = strlen(_path);
	const size_t blksize = (npath << 1) + ncmd + _NULLCHAR_BUFFER_SPACE;
	const size_t ndstbuf = blksize - npath;

	char *memblk = (char *) malloc(blksize);
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
		snprintf(path, ndstbuf, "%s/%s", tok, cmd);

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
