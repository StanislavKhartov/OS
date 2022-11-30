#include "stdafx.h"
#include <iostream>
#include <sstream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::string buffer;
	std::getline(std::cin, buffer);
	std::stringstream ss(buffer);
	int x;
	int sum = 0;	
	while(ss >>x){
		sum += x;
	};

	std::cout << "Answer " << sum;

	return 0;
}