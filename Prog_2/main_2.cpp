#include "functions_2.h"

int main()
{
	char sum[4];
	Serv serv;
	
	serv.setup();
	setConnection(serv);
	
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
	while(true)
	{
		int ex_code = recv(serv.conn_sock, &sum, 4, 0);
		if(getchar() == '\n') break;
		
		switch(ex_code)
		{
		case -1: 
		case 0:
			reconnection(serv);
		}

		int num = std::stoi(std::string(sum));
		
		if(std::abs(num) >= 100 && num % 32 == 0)
			std::cout << "\x1b[42m" << num << "\x1b[0m\n";
		else
			std::cout << "\x1b[41mError " << num << "\x1b[0m\n";
	}
	
	return 0;
}
