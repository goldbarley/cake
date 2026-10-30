#ifndef CAKE_H_
#define CAKE_H_ 1

#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>

#define CAKE_MAX_PATH_LEN (4096U)

#if defined(__GNUC__) || defined(__clang__)
#define CAKE_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#define CAKE_LIKELY(expr) __builtin_expect(!!(expr), 1)
#define CAKE_HOT __attribute__((__hot__))
#define CAKE_COLD __attribute__((__cold__))
#else
#define CAKE_UNLIKELY(expr) (expr)
#define CAKE_LIKELY(expr) (expr)
#define CAKE_HOT
#define CAKE_COLD
#endif /* __GNUC__ || __clang__ */

#ifdef __cplusplus
#define restrict __restrict
#endif /* __cplusplus */

extern char *cc;
extern char *projname;

/* Return codes */
enum
{
	RET_OK = 0,
	RET_ERR = -1
};

typedef enum cmd_buffer_type
{
	CMD_BUFFER_TYPE_FIFO = 0x00000000,
	CMD_BUFFER_TYPE_MAILBOX = 0x00000001,
	CMD_BUFFER_TYPE_IMMEDIATE = 0x00000002,
	CMD_BUFFER_TYPE_MAX_ENUM = 0x7FFFFFFF
} cmd_buffer_type_t;

typedef struct cmd_buffer cmd_buffer_t;

typedef struct cmd_buffer_info
{
	size_t cap;
	cmd_buffer_type_t type;
} cmd_buffer_info_t;

typedef struct str
{
	char *s;
	size_t len;
} str_t;

typedef struct str cmdarg_t;

typedef struct cmd
{
	char *cmd;
	cmdarg_t *args;
	unsigned int argc;
} cmd_t;

int set_cc(const char *s);
int set_projname(const char *s);
int find_cmd(const char *cmd); /* DONE */
int find_dir(const char *path); /* DONE */
int find_file(const char *path); /* DONE */
int include_dir(const char *path); /* PENDING */
int create_cmd_buffer(cmd_buffer_info_t *restrict info,
		      cmd_buffer_t *restrict buffer); /* PENDING */
int submit_cmd(cmd_t *cmd); /* PENDING */
void done(void);

#endif /* CAKE_H_ */
