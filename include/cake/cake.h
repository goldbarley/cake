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
#define CAKE_FORMAT_PRINTF(a, b) __attribute__((__format__(__printf__, a, b)))
#else
#define CAKE_UNLIKELY(expr) (expr)
#define CAKE_LIKELY(expr) (expr)
#define CAKE_HOT
#define CAKE_COLD
#define CAKE_FORMAT_PRINTF(a, b)
#endif /* __GNUC__ || __clang__ */

#ifdef __cplusplus
#define restrict __restrict
#endif /* __cplusplus */

#define DISCARD(x) ((void)(x))

/* Return codes */
enum
{
	RET_OK = 0,
	RET_ERR = -1
};

typedef struct context context_t;

typedef enum buffer_type
{
	BUFFER_TYPE_FIFO = 0x00000000,
	BUFFER_TYPE_MAILBOX = 0x00000001,
	BUFFER_TYPE_IMMEDIATE = 0x00000002,
	BUFFER_TYPE_MAX_ENUM = 0x7FFFFFFF
} buffer_type_t;

typedef enum cmd_buffer_type
{
	CMD_BUFFER_TYPE_FIFO = BUFFER_TYPE_FIFO,
	CMD_BUFFER_TYPE_MAILBOX = BUFFER_TYPE_MAILBOX,
	CMD_BUFFER_TYPE_IMMEDIATE = BUFFER_TYPE_IMMEDIATE,
	CMD_BUFFER_TYPE_MAX_ENUM = BUFFER_TYPE_MAX_ENUM
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
	cmdarg_t *argv;
	unsigned int argc;
} cmd_t;

#define CAKE_DEFAULT_ALLOC_ALIGNMENT (_Alignof(max_align_t))

typedef void *(*ptf_alloc_t)(size_t size, void *arg);
typedef void *(*ptf_alignedalloc_t)(size_t size, size_t align, void *arg);
typedef void (*ptf_free_t)(void *mem, void *arg);
typedef void *(*ptf_realloc_t)(void *orig, size_t size, size_t align, void *arg);

typedef struct alloccb
{
	ptf_alloc_t fp_alloc;
	ptf_free_t fp_free;
	ptf_realloc_t fp_realloc;
	void *arg;
} alloccb_t;

typedef void *(*callback_t)(void *);

CAKE_FORMAT_PRINTF(4, 5)
void check_ret(int ret, callback_t errcb, void* arg, const char *msg, ...);
int get_context(context_t **restrict ctx, const alloccb_t *restrict alloc);
int set_cc(context_t *restrict ctx, const char *restrict s,
	   const alloccb_t *restrict alloc);
int set_projname(context_t *restrict ctx, const char *restrict s,
		 const alloccb_t *restrict alloc);
const char *get_cc(context_t *ctx);
const char *get_projname(context_t *ctx);
int add_cmdargs(const char **args, cmdarg_t *argv, size_t argc);
/* POSIX: DONE, Win32: PENDING */
int find_cmd(const char *cmd,
	     const alloccb_t *restrict alloc);
/* POSIX: DONE, Win32: PENDING */
int find_dir(const char *path);
/* POSIX: DONE, Win32: PENDING */
int find_file(const char *path);
/* PENDING */
int include_dir(const char *path);
/* PENDING */
int create_cmd_buffer(cmd_buffer_info_t *restrict info,
		      cmd_buffer_t *restrict buffer);
/* PENDING */
int submit_cmd(cmd_t *cmd);
/* PARTIALLY IMPLEMENTED */
void done(context_t *ctx);

#endif /* CAKE_H_ */
