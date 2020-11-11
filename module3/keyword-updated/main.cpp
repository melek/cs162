#include "main.h"
#include "KeywordIndex.h"

int main(int argc, char **args, char**envp) {
    KeywordIndex index;
    
    std::cin >> index;
    index.sort();
    std::cout << index;

    return 0;
}
