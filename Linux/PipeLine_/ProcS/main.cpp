#include <iostream>
#include <sstream>

int main() {
    std::string buffer;
    std::getline(std::cin, buffer);
    std::stringstream ss(buffer);
    int x;
    int sum = 0;
    while (ss >> x) {
        sum += x;
    };

    std::cout << "Answer " << sum << "\n";

    return 0;
}