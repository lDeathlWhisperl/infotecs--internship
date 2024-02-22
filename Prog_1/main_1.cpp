#include <signal.h>

#include "functions_1.h"

static void* thread(void* arg)
{
	Args *args = (Args*) arg;
	std::string str;
	timespec time;
	
	while(args->isActive)
	{
		clock_gettime(CLOCK_REALTIME, &time);
		time.tv_sec += 1;

		if(pthread_mutex_timedlock(&args->mutex, &time)) continue;

		str = args->buf;
		args->buf.clear();
		
		std::cout << "Result string: " << str << '\n';
		if(write(args->sock, std::to_string(sum(str)).c_str(), 4) == -1) 
			reconnection(*args);
		
		pthread_mutex_unlock(&args->mutex);
		sleep(1);
	}
	
	pthread_exit((void*) 0);
}

int main()
{
	std::string str;
	pthread_t thr;
	Args args;
	
	setConnection(args);
	
	pthread_create(&thr, nullptr, &thread, &args);
	signal(SIGPIPE, SIG_IGN); 
	
	while(true)
	{
		pthread_mutex_lock(&args.mutex);
		
		retry:
		std::cout << "> ";
		std::getline(std::cin, str);
		if(!isRequest(str))
		{
			if(str == "exit") break;
			std::cout << "\x1b[41mInvalid input\x1b[m\n";
			goto retry;
		}
		
		process(str);
		args.buf = str;
		
		pthread_mutex_unlock(&args.mutex);
		sleep(1);
	}
	
	args.isActive = false;
	pthread_join(thr, nullptr);
	signal(SIGPIPE, SIG_DFL); 
	
	return 0;
}
