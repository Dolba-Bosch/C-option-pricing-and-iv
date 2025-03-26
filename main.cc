#include <iostream>
#include "main.ih"
#include <iomanip>

int main()
{
    std::cout << std::setprecision(10);
    std::cout << AmCall(4772, 4700, 0.25, 0.02, 0.05, 2184, 10) << std::endl;
    std::cout << AmPut(4772, 4700, 0.25, 0.02, 0.05, 2184, 10) << std::endl;
    std::cout << CallIV(4772, 4700, 0.02, 0.05, 2184, 10, 2392.6765) << std::endl;
    std::cout << PutIV(1136.99, 865, 0, 0.01, 8, 100, 0.11) << std::endl;
    std::cout << CallIV(1141.48, 2500, 0, 0.01, 1078, 100, 0.10) << std::endl;
}
