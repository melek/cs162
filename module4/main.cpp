#include "main.h"

int main(int argc, char **argv, char **envp)
{
    string myStr = "Please enter a string: ";
    std::cout << myStr << std::endl;
    std::cin >> myStr;
    std::cout << myStr << std::endl;
    for(int i = 0; i < myStr.length(); i++) 
        std::cout << myStr[i] << " ";
    std::cout << std::endl;
    string secondStr = myStr;
    myStr = "What now??";
    std::cout << myStr << " ... " << secondStr << std::endl;
    return 0;
}

