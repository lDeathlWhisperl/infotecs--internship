#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct Args
{
	std::string buf;
	pthread_mutex_t mutex;
	
	bool isActive = true;
	
	int sock;
	sockaddr_in addr;
	
	Args();
	
	~Args();
};
