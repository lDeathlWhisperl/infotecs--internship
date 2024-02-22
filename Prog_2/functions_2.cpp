#include "functions_2.h"

void setConnection(Serv& srv)
{
	system("clear");
	socklen_t sock_size = sizeof(srv.cl_addr);
	
	fcntl(srv.sock, F_SETFL, O_NONBLOCK);
	while(true)
	{
		srv.conn_sock = accept(srv.sock, (sockaddr*)&srv.cl_addr, &sock_size);
		if(srv.conn_sock == -1)
		{
			std::cout << "\x1b[0;0HConnecting  " << std::flush;
			sleep(1);
		}
		else break;
	}
	fcntl(srv.sock, F_SETFL, ~O_NONBLOCK);
	
	std::cout << "\x1b[0;0HSuccess!    \n";
}

void reconnection(Serv &serv)
{
	system("clear");
	std::cout << "Disconnected" << std::flush; 
	sleep(1);
	
	close(serv.sock);
	serv.sock = socket(AF_INET, SOCK_STREAM, 0);
	serv.setup();
	
	setConnection(serv);
}
