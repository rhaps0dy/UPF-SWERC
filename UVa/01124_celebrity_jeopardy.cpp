#include <iostream>
#include <string>

int main()
{
    std::string inputLine;
    
    while (std::getline(std::cin, inputLine))
    {
        std::cout << inputLine << std::endl;
    }
    
    return 0;
}
