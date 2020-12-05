#pragma once
#include <iostream>
#include <cstring>

struct    word
{
     char           *    data;                    // C-string
     unsigned int   *    lines;                   // Line number array
     int                 size;
     int                 capacity;
     word();                                      // Default constructor
     ~word();                                     // Default destructor
     word(char *);                                // Parameterized constructor
     void erase();                                // Erase word and lines
     void add_line(unsigned int);                 // Add line to line list for word

     word & operator = (const word &);            // Copy assignment
     
};

bool operator == (const word &, const word &);
bool operator >  (const word &, const word &);
