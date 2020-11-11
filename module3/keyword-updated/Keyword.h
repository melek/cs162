#pragma once
#include <string>
#include <iostream>

#define MAXLINES 50

struct Keyword {
    std::string word;
    int lines[MAXLINES];
    int count;
    int linesFound;

    // Constructors
    Keyword();                 // Default constructor
    Keyword(Keyword &);        // Copy constructor
    Keyword(std::string);      // Conversion constructor
    Keyword(std::string, int); // Conversion constructor + addline call

    // Assignment Operators
    Keyword & operator = (const Keyword &);     // Copy Assignment
    Keyword & operator = (Keyword &&);          // Move Assignment

    int addLine(int); // Increments count and adds line if unique
    void print(int); // Prints the Keyword's data with an index line
};

bool operator == (const Keyword &, const Keyword &);
bool operator >  (const Keyword &, const Keyword &);

std::ostream & operator << (std::ostream &, const Keyword &);
std::istream & operator >> (std::istream &, Keyword &);

