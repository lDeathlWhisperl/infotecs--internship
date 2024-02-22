#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct Serv
{
	int sock;
	int conn_sock;
	
	sockaddr_in addr, cl_addr;
	
	Serv();
	
	void setup();
	
	~Serv();
};
