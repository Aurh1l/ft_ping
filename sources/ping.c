#include "../includes/main.h"

//static inline void icmp_request()
//{
//	struct icmphdr icmphdr;
//	ft_bzero(&icmphdr, sizeof(icmphdr));
//	icmphdr.type = ICMP_ECHO;
//	icmphdr.code = 0;
//}

void ping(char *host)
{
	int sock;
	struct sockaddr_in sock_addr;

	ft_bzero(&sock_addr, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = 0;

	if (inet_pton(AF_INET, host, &sock_addr) != 1)
	{
		log_error(host, "Name or service not known");
		exit(1);
	}

	ft_bzero(host, strlen(host));
	inet_ntop(AF_INET, &sock_addr,host, INET_ADDRSTRLEN);
	printf("IP address: %s\n\n", host);

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	if (sock == -1)
	{
		log_error(host, strerror(errno));
		exit(1);
	}

	close(sock);
}
