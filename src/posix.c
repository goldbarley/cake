#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cake/cake.h"

#define _NULLCHAR_BUFFER_SPACE (2U)

_Bool find_cmd(const char *cmd)
{
	if (!cmd)
		return false;

	if (strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return true;

	const size_t ncmd = strlen(cmd);
	char *_path = getenv("PATH");
	if (!_path)
		return false;

	const size_t npath = strlen(_path);
	const size_t blksize = (npath << 1) + ncmd + _NULLCHAR_BUFFER_SPACE;
	const size_t ndstbuf = blksize - npath;

	char *memblk = (char *) malloc(blksize);
	if (!memblk)
		return false;

	char *memblk2 = memcpy(memblk, _path, npath);
	memblk2[npath] = 0;

	char *path = memblk + npath;

	char *tok = strtok(memblk, ":");
	while (tok)
	{
		snprintf(path, ndstbuf, "%s/%s", tok, cmd);

		if (access(path, X_OK) == 0)
		{
			free(memblk);
			return true;
		}
		tok = strtok(NULL, ":");
	}

	free(memblk);
	return false;
}

#undef _NULLCHAR_BUFFER_SPACE

static inline
_Bool _fsstatus(const char *restrict path, struct stat *restrict s)
{
	if (!path || !s)
		return false;

	if (lstat(path, s) != 0)
		return false;

	if (S_ISLNK(s->st_mode))
		if (stat(path, s) != 0)
			return false;

	return true;
}

_Bool find_dir(const char *path)
{
	struct stat s;

	return _fsstatus(path, &s) && S_ISDIR(s.st_mode);
}

_Bool find_file(const char *path)
{
	struct stat s;

	return _fsstatus(path, &s) && S_ISREG(s.st_mode);
}
