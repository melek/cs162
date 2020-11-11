#pragma once
#include <iostream>

struct element {
    int data;
    element();                  // Default constructor
    element(const element &);   // Copy constructor
    element(int);               // Converting constructorn
    
    element & operator = (const element &); // Copy assignment
    element & operator = (element &&);      // Move assignment
    element & operator = (int &);           // Copy from int assignment
};

bool operator == (element &, element &);
bool operator != (element &, element &);
bool operator >  (element &, element &);

std::ostream & operator << (std::ostream &, const element &); // Stream insertion
std::istream & operator >> (std::istream &, element &);       // Stream extraction

