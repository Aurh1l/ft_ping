#ifndef FT_PING_MAIN_H
#define FT_PING_MAIN_H
#define NB_OPTIONS 2
#define VERBOSE_OPTION 0

//==============================================================================//
//--------------------------------- INCLUDES -----------------------------------//
//==============================================================================//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <netinet/ip_icmp.h>

//==============================================================================//
//--------------------------------- FUNCTIONS ----------------------------------//
//==============================================================================//

int         main(int ac, char **av);
int         ft_strcmp(const char *s1, const char *s2);
void	    *ft_memset(void *b, int c, size_t len);
void 		log_info(char *msg);
void 		log_error(char *host, char *msg);

#endif //FT_PING_MAIN_H
