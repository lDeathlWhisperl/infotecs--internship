#include <iostream>

#include "Args.h"

bool isRequest(const std::string &str);

inline bool isEven(int x)
{
	return !(x & 1);
}

void process(std::string &str);

int sum(std::string &str);

void setConnection(Args &args);

void reconnection(Args &args);
