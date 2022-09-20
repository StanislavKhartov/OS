#include <iostream>
#include "/home/stanislave/CLionProjects/Dll/library.h"

int main()
{
    Vector test1(Number(1), Number(0));
    Vector test2(Number(1), Number(1));
    Vector addTest;
    addTest.setValue(test1.add(test2));
    std::cout << addTest.getPolarRadius() << "\n";
    std::cout << addTest.getPolarAngle() << "\n";
    return 0;
}
