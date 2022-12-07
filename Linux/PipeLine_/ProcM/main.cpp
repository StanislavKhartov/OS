#include <iostream>
#include <sstream>

int main()
{
	std::string buffer;
	std::getline(std::cin, buffer);
	std::stringstream ss(buffer);
	int x;
	while (ss >> x) {
		std::cout << x * 7 << " ";
	};
	std::cout << std::endl;
	return 0;
}
