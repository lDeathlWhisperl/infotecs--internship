#include "Args.h"

Args::Args()
{
	pthread_mutex_init(&mutex, nullptr);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t addr_size;
		
	addr.sin_family = AF_INET;
	addr.sin_port = htons(25565);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr_size = sizeof(addr_size);
}
	
Args::~Args()
{
	pthread_mutex_destroy(&mutex);
	close(sock);
	shutdown(sock, SHUT_RDWR);
}
