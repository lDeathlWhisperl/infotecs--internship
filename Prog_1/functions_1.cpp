#include "functions_1.h"
#include <vector>
#include <algorithm>
#include <fcntl.h>


bool isRequest(const std::string &str)
{
	if(str.empty() || str.size() > 64) return false;
	
	for(size_t i = 0; i < str.size(); ++i)
		switch(str[i])
		{
		case '-':
			if(i == str.size()-1 || !isdigit(str[i+1])) return false;
			break;
		default:
			if(!isdigit(str[i])) return false;
		}
	
	return true;
}

void process(std::string &str)
{
	std::vector<int> nums;
	for(size_t i = 0; i < str.size(); ++i)
	{
		switch(str[i])
		{
		case '-':
			nums.push_back((str[i+1] - '0') * -1);
			++i;
			break;
		default: nums.push_back(str[i] - '0');
		}
	}
	
	std::sort(nums.begin(), nums.end(), [](int a, int b){ return a > b; });
	
	str.clear();
	for(const auto& n : nums)
		if(n < 0)
		{
			str.push_back('-');
			str.push_back(n * -1 + '0');
		}
		else
			str.push_back(n + '0');

	for(size_t i = 0; i < str.size(); ++i)
	{
		if(str[i] == '-' && isEven(str[i+1]))
			str.erase(str.begin() + i);
		
		if(isEven(str[i]))
		{
			str[i] = 'B';
			str.insert(i++, "K");
		}
	}
}

int sum(std::string &str)
{
	int res = 0;
	
	for(size_t i = 0; i < str.size(); ++i)
	{
		if(str[i] == '-')
		{
			res -= (str[i+1] - '0');
			++i;
 		}
		else if(!isdigit(str[i])) 
			continue;
		else 
			res += (str[i] - '0');
	}
	
	return res;
}

void setConnection(Args &args)
{
	system("clear");
	int sock;
	
	while(true)
	{
		sock = connect(args.sock, (sockaddr*)&args.addr, sizeof(args.addr));
		if(sock == -1)
		{
			std::cout << "\x1b[0;0HConnecting  " << std::flush;
			sleep(1);
		}
		else break;
	}
	
	std::cout << "\x1b[0;0HSuccess!    \n";
}

void reconnection(Args &args)
{
	system("clear");
	std::cout << "Disconnected"; 
	
	close(args.sock);
	args.sock = socket(AF_INET, SOCK_STREAM, 0);
	setConnection(args);
}
