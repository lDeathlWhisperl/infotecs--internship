#include <strings.h>

#include "Serv.h"

Serv::Serv()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
		
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(25565);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}
	
void Serv::setup()
{
	int optval = 1;
		
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
	{
		perror("setsockopt");
		exit(1);
	}
			
	if(bind(sock, (sockaddr*)&addr, sizeof(addr)) == -1) 
	{
		perror("bind");
		exit(2);
	}
		
	if(listen(sock, 0) == -1)
	{
		perror("listen");
		exit(3);
	}
}
	
Serv::~Serv()
{
	close(sock);
	shutdown(conn_sock, SHUT_RDWR);
}
