#ifndef FT_PING_MAIN_H
#define FT_PING_MAIN_H
#define NB_OPTIONS 2
#define VERBOSE_OPTION 0
#define RECV_TIMEOUT_USEC 100000

//==============================================================================//
//--------------------------------- INCLUDES -----------------------------------//
//==============================================================================//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//==============================================================================//
//--------------------------------- FUNCTIONS ----------------------------------//
//==============================================================================//

int         main(int ac, char **av);
void 		ping(const char *host);
void 		log_info(const char *msg);
void 		log_error(const char *host, const char *msg);

void		ft_bzero(void *s, size_t n);
int         ft_strcmp(const char *s1, const char *s2);
void	    *ft_memset(void *b, int c, size_t len);

#endif //FT_PING_MAIN_H
