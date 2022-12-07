#include <iostream>
#include <sstream>
#include <cmath>

int main()
{
    std::string buffer;
    std::getline(std::cin, buffer);
    std::stringstream ss(buffer);
    int x;
    while (ss >> x) {
        std::cout << std::pow(x, 3) << " ";
    };
    std::cout << std::endl;
    return 0;
}