#include "../includes/main.h"

 static inline short checksum(void *buffer, int len)
 {
	 unsigned short *buf = buffer;
	 unsigned int sum=0;
	 unsigned short result;

	 for ( sum = 0; len > 1; len -= 2 )
		 sum += *buf++;
	 if ( len == 1 )
		 sum += *(unsigned char*)buf;
	 sum = (sum >> 16) + (sum & 0xFFFF);
	 sum += (sum >> 16);
	 result = ~sum;
	 return result;
 }

static inline void send_icmp_echo(const char *host, int sock, struct sockaddr_in *sock_addr)
{
	struct icmphdr icmphdr;
	ft_bzero(&icmphdr, sizeof(icmphdr));

	icmphdr.type = ICMP_ECHO;
	icmphdr.code = 0;
	icmphdr.un.echo.id = getpid();
	icmphdr.un.echo.sequence = 1; // TODO: increment in loop
	icmphdr.checksum = checksum(&icmphdr, sizeof(icmphdr));

	if (sendto(sock, &icmphdr, sizeof(icmphdr), 0, (struct sockaddr*)sock_addr, sizeof(*sock_addr)) <= 0)
	{
		log_error(host, "Packet sending failed");
		exit(1);
	}
}

static inline struct addrinfo *dns_lookup(const char *host) {
	struct addrinfo hints;
	struct addrinfo *res;

	ft_bzero(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	if (getaddrinfo(host, NULL, &hints, &res) != 0)
	{
		log_error(host, "Could not resolve hostname");
		exit(1);
	}
	return res;
}

void ping(const char *host)
{
	int sock;
	char ip[INET_ADDRSTRLEN];
	struct sockaddr_in sock_addr;
	struct timeval recv_timeout;
	struct addrinfo const *addrinfo;

	ft_bzero(&sock_addr, sizeof(sock_addr));
	ft_bzero(&ip, sizeof(ip));
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = 0;

	addrinfo = dns_lookup(host);
	inet_ntop(AF_INET, &addrinfo->ai_addr->sa_data[2], ip, sizeof(ip));

	if (inet_pton(AF_INET, ip, &sock_addr) != 1)
	{
		log_error(host, "Not a valid address");
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

	send_icmp_echo(host, sock, &sock_addr);
	close(sock);
}
