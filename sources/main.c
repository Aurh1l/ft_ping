#include "../includes/main.h"

static inline void help(void)
{
    dprintf(1, "Usage: ft_ping [OPTION...] HOST ...\n"
               "-h, --help      give this help list"
               "-v, --verbose   verbose output");
}

static inline void parse_argument(char *options, const char *arg)
{
    if (ft_strcmp("-v", arg) == 0 || ft_strcmp("--verbose", arg))
    {
        options[VERBOSE_OPTION] = 1;
    }
	else
	{
		help();
		exit(1);
	}
}

int main(int ac, char **av)
{
    char *options[NB_OPTIONS];

    ft_memset(options, 0, NB_OPTIONS);
    if (ac < 2)
    {
        help();
        exit(1);
    }

    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] == '-')
		{
			parse_argument((char*) options, av[i]);
		}
        else
		{
			// call ping
		}
    }
}
