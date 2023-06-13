#include "../includes/main.h"

void log_info(const char *msg)
{
	dprintf(STDOUT_FILENO, "%s\n", msg);
}

void log_error(const char *host, const char *msg)
{
	dprintf(STDERR_FILENO, "ft_ping: %s: %s\n", host, msg);
}
