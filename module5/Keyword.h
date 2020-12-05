#pragma once
#include "string.h"

#define KEYWORD_H_CHUNK     10
#define SUCCESS_COUNT_ONLY  0
#define SUCCESS_LINE_ADDED  1

class Keyword {
  private:
    string word;
    int count;
    int * lines;                // Capacity managed array
    int lines_size;             // of lines the Keyword is found on
    int lines_capacity; 

  public:
    Keyword();                  // Default constructor
    Keyword(const Keyword &);   // Copy constructor
    Keyword(string);            // Conversion constructor
    Keyword(string, int);       // Conversion constructor + addline call
    ~Keyword();                 // Destructor

    // Assignment Operators
    Keyword & operator = (const Keyword &);     // Copy Assignment
    Keyword & operator = (Keyword &&);          // Move Assignment

    // Subscript returns characters from 'word'
    char & operator [] (int);                    // Subscript
    const char & operator [] (int) const;        // Const Subscript

    string get_word() const;
    int get_count() const;
    int get_ls() const;     // Getter for lines_size;
    int get_lc() const;     // Getter for lines_capacity;
    int * get_lines() const;   
    int get_line(int) const;// Getter for lines[int]
 
    void print(int); // Prints the Keyword's data with an index line

    int addLine(int); // Increments count and adds line if unique
};

bool operator == (const Keyword &, const Keyword &);
bool operator >  (const Keyword &, const Keyword &);
bool operator != (const Keyword &, const Keyword &);
bool operator <  (const Keyword &, const Keyword &);
bool operator >= (const Keyword &, const Keyword &);
bool operator <= (const Keyword &, const Keyword &);

std::ostream & operator << (std::ostream &, const Keyword &);
std::istream & operator >> (std::istream &, Keyword &);

