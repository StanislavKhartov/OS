﻿#include "stdafx.h"
#include <iostream>
#include <sstream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::string buffer;
	std::getline(std::cin, buffer);
	std::stringstream ss(buffer);
	int x;
	while (ss >> x) {
		std::cout << pow(x, 3) << " ";
	};
	std::cout << std::endl;
	return 0;
}