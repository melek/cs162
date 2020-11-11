#pragma once
#include <iostream>
#include "element.h"

class list {
    private:
        element * data;
        int size;
        int capacity;

    public:
        
        // Constructor
        list();                 // Default
        list(const list &);     // Copy

        // Mutators
        list & operator = (const list &);   // Copy assignment
        list & operator = (list &&);        // Move assignment

        void insert(element);   // List ADT insert
        void insert(int);
        void remove(element);   // List ADT remove all instances of element
        void remove(int);

        // Accessors
        element & at(int);                          // Array access function
        element & operator [] (int);                // Subscript operator
        const element & operator [] (int) const;    // Const subscript operator

        int length();   // List ADT
        int find(element);  // List ADT
        int find(int);    

};

bool operator == (const list &, const list &);  // Relational operator
bool operator >  (const list &, const list &);  // Relational operator

std::ostream operator << (std::ostream &, const list &);    // Stream insertion
std::istream operator << (std::istream &, list &);          // Stream insertion

