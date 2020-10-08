#include "main.h"

int main(int argc, char **args, char **envp)
{
    std::cout << "Testing the C Standard Library" << std::endl;

    std::cout << "1. assert.h: void assert(int)" << std::endl;
    assert(false);

    return 0;
}
