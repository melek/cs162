#pragma once
#include <iostream>
#include "word.h"

struct    list
{
     word      *    data;                    // Word array
     int            capacity;                // capacity
     int            size;                    // size

     list();                  // Constructor
     ~list();                 // Destructor
     void insert(word *);     // Add word to the list
     int find(word *);        // Return index of word in list
};

