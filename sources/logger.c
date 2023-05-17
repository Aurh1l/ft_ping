#include "../includes/main.h"

void log_info(char *msg)
{
	dprintf(STDOUT_FILENO, "%s\n", msg);
}

void log_error(char *host, char *msg)
{
	dprintf(STDERR_FILENO, "ft_ping: %s: %s\n", host, msg);
}
