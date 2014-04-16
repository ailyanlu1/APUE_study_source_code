#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

#if defined (BSD) || defined (MACOS)

	#include <sys/socket.h>
	#include <netinet/in.h>

#endif

void print_family(struct addrinfo *aip)
{
	printf("family");
	switch(aip->ai_family)
	{
		case AF_INET:
		printf("inet");
		break;

		case AF_INET6:
		printf("inet6");
		break;

		case AF_UNIX:
		printf("unix");
		break;

		case AF_UNSPEC:
		printf("unspecified");
		break;
	
		default:
		printf("unknowm");
	}
}

void print_type(struct addrinfo *aip)
{
	printf(" type ");
	switch (aip->ai_socktype)
	{
		case SOCK_STREAM :
		printf("stream");
		break;
	
		case SOCK_DGRAM:
		printf("datagram");
		break;
	
		case SOCK_SEQPACKET:
		printf("seqpacket");
		break;

		case SOCK_RAW:
		printf("raw");
		break;

		default:
			printf("unknown (%d)",aip->ai_socktype);
	}
}


void print_protocol(struct addrinfo *aip)
{
	printf(" protocol ");
	switch (aip->ai_protocol)
	{
		case 0:
		printf("default");
		break;
	
		case IPPROTO_TCP:
		printf("TCP");
		break;

		case IPPROTO_UDP:
		printf("UDP");
		break;

		case IPPROTO_RAW:
		printf("RAW");
		break;

		default:
			printf("unknown (%d)",aip->ai_protocol);
	}
}

void print_flags(struct addrinfo* aip)
{
	printf(" flags ");

	if(aip->ai_flags == 0)
	{
		printf(" 0");
	}
	else
	{
		if(aip->ai_flags & AI_PASSIVE)
		{
			printf("passive");
		}

		if(aip->ai_flags & AI_CANONNAME)
		{
			printf(" canon");
		}

		if(aip->ai_flags & AI_NUMERICHOST)
		{
			printf(" numhost");
		}

#if defined (AI_NUMERICSERV)

		if(aip->ai_flags & AI_NUMERICSERV)
		{
			printf(" numserv");
		}

#endif

#if defined (AI_V4MAPPED)

		if(aip->ai_flags & AI_V4MAPPED)
		{
			printf(" v4mapped");
		}

#endif

#if defined (AI_ALL)

		if(aip->ai_flags & AI_ALL)
		{
			printf(" all");
		}

#endif
		
	}
}

int main(int argc,char* argv[])
{
	struct addrinfo *aip,*ailist;
	struct addrinfo hint;

	struct sockaddr_in *sinp;

	const char* add;

	int err;
	
	char abuf[INET_ADDRSTRLEN];

	if(argc != 3)
	{
		printf("usage : %s nodename service\n",argv[0]);
		return 0;
	}

	hint.ai_flags = AI_CANONNAME;
	hint.ai_family = 0;
	hint.ai_socktype = 0;
	hint.ai_protocol = 0;
	hint.ai_addrlen = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	
	if((err = getaddrinfo(argv[1],argv[2],&hint,&ailist)) != 0)
	{
		printf(" getaddrinfo error\n");
		return 0;
	}

	for(aip = ailist; aip != NULL;aip = aip->ai_next)
	{
		print_flags(aip);
		print_family(aip);
		print_type(aip);
		print_protocol(aip);
		printf("\n\thost %s",aip->ai_canonname ? aip->ai_canonname:"-");
		if(aip->ai_family == AF_INET)
		{
			sinp = (struct sockaddr_in*)aip->ai_addr;
			add = inet_ntop(AF_INET,&sinp->sin_addr,abuf,INET_ADDRSTRLEN);
			printf(" address %s",add ? add : "unknown");
			printf(" port %d",ntohs(sinp->sin_port));
		}
		
		printf("\n");
	}
	
	return 0;
}
