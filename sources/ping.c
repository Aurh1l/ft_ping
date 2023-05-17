#include "../includes/main.h"

static inline short checksum(void *buffer, int len)

static inline void send_icmp_echo()
{
	struct icmphdr icmphdr;
	ft_bzero(&icmphdr, sizeof(icmphdr));

	icmphdr.type = ICMP_ECHO;
	icmphdr.code = 0;
	icmphdr.un.echo.id = getpid();
	icmphdr.un.echo.sequence = 1; // TODO: increment in loop
}

void ping(const char *host)
{
	int sock;
	struct sockaddr_in sock_addr;
	struct timeval recv_timeout;

	ft_bzero(&sock_addr, sizeof(sock_addr));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = 0;

	if (inet_pton(AF_INET, host, &sock_addr) != 1)
	{
		log_error(host, "Name or service not known");
		exit(1);
	}

	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	if (sock == -1)
	{
		log_error(host, strerror(errno));
		exit(1);
	}

	recv_timeout.tv_sec = 0;
	recv_timeout.tv_usec = RECV_TIMEOUT_USEC;

	if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout)) == -1)
	{
		log_error(host, strerror(errno));
		exit(1);
	}

	close(sock);
}
