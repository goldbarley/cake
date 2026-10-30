#ifndef CAKE_H_
#define CAKE_H_ 1

#ifdef _WIN32
#define CAKE_CMD_CC /* Fill */
#define CAKE_CMD_FIND /* Fill */
#else
#define CAKE_CMD_CC "cc"
#define CAKE_CMD_FIND "command -v"
#endif /* _WIN32 */

#define CAKE_MAX_PATH_LEN (4096U)

#ifndef false
#define false (0)
#endif /* false */

#ifndef true
#define true (1)
#endif /* true */

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

typedef struct cmd
{
	char *cmd;
	char **args;
} cmd_t;

_Bool find_cmd(const char *cmd);

_Bool find_dir(const char *path);

_Bool find_file(const char *path);

_Bool include_dir(const char *path);

#endif /* CAKE_H_ */
