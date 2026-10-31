#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cake/cake.h"

#define _NULLCHAR_BUFFER_SPACE (2U)

int find_cmd(const char *cmd, const alloccb_t *restrict alloc)
{
	if (!cmd)
		return RET_ERR;

	if (strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return RET_OK;

	const size_t ncmd = strlen(cmd);
	char *_path = getenv("PATH");
	if (!_path)
		return RET_ERR;

	const size_t npath = strlen(_path);
	const size_t blksize = (npath << 1) + ncmd + _NULLCHAR_BUFFER_SPACE;
	const size_t ndstbuf = blksize - npath;

	char *memblk = (char *) malloc(blksize);
	if (!memblk)
		return RET_ERR;

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
			return RET_OK;
		}
		tok = strtok(NULL, ":");
	}

	free(memblk);
	return RET_ERR;
}

#undef _NULLCHAR_BUFFER_SPACE

static inline
int _fsstatus(const char *restrict path, struct stat *restrict s)
{
	if (!path || !s)
		return RET_ERR;

	if (lstat(path, s) != 0)
		return RET_ERR;

	if (S_ISLNK(s->st_mode))
		if (stat(path, s) != 0)
			return RET_ERR;

	return RET_OK;
}

int find_dir(const char *path)
{
	struct stat s;

	return _fsstatus(path, &s) && S_ISDIR(s.st_mode);
}

int find_file(const char *path)
{
	struct stat s;

	return _fsstatus(path, &s) && S_ISREG(s.st_mode);
}
