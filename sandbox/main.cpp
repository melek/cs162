#include "main.h"

// 'class' here could be 'typename'; they are equivalent.
template <class T>
T add2(T a) {
    return a + 2;
}

int main(int argc, char **args, char **envp)
{
    std::cout << "Testing the C Standard Library" << std::endl;

    std::cout << "1. assert.h: void assert(int)" << std::endl;
    assert(true);

    std::cout << "2. Template: ";
        int a = 5;
        float f = 0.5;
        a = add2<int>(a);
        f = add2<float>(f);

    std::cout << "Int(5) + 2: " << a << " - " << f << std::endl;


    return 0;
}
