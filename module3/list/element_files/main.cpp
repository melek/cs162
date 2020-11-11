#include "main.h"
#include "element.h"
#include <iostream>

int main(int argc, char ** args, char ** envp) {
    element myEl = 5;
        
    element el2;
    el2 = myEl;
    myEl = *(new element(13));

    std::cout << "myEl: " 
              << myEl
              << "   el2: "
              << el2
              << std::endl;
    
    std::cout << "myEl == el2: " 
              << (myEl == el2)
              << std::endl;
    
    std::cout << "myEl > el2: " 
              << (myEl > el2)
              << std::endl;
    
    return 0;
}
