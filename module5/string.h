#pragma once

/*
    String Interface

    Manages an array of characters to be treated as a null-terminated string.
    Only uses iostream.

    Creates and manages a sentinel array with a 'size' variable so we don't
    need a loop method to calculate size.

    We will implement default class members:
    - Private data
        - Character pointer to a C String-style null-character terminated array.
        - Integer size, which is a count of characters in the array.
          This will be modified whenever the array is changed.
        - Integer capacity of the array, because re-allocating memory for each
          character-length change is expensive.
    - Public members
        - Constructors: Default, Copy, and Move.
        - Assignment operators: Copy and Move.
        - Mutators: 
            - set(const char *) will set the string to a new value
            - set(const string) is equivalient the copy assignment operator
            - Insert: Both positional and ordered insert.
            - insert(char), insert(string), insert(char, int), insert(string, int)
            - Remove: Both positional and ordered removal.
            - remove() pops last char, remove(pos), remove(pos, size) 
            - is_empty() and is_full() are boilerplate helpers to check size
        - Getters: size(), capacity(), cstring() will return the member variables.
    - Helper functions 
        - Relational operators & helper function 'strcmp()'
        - Stream operators
*/

#include <iostream>
#define STRING_H_CHUNK  5

class string {
  private:
    char *         cstring;               // Character string
    int            size;                // Number of characters stored
    int            capacity;            // Maximum number of characters + \0

  public:
    string();                           // Default constructor
    string(const string &);             // Copy constructor
    string(const char *);               // Parameterized copy constructor
    string(string &&);                  // Move constructor
    ~string();                          // Destructor

    string & operator = (const string &);   // Copy assignment
    string & operator = (const char *);     // Parameterized copy assignment
    string & operator = (string &&);        // Move assignment
     
    char & operator[] (int);             // Alias for at()
    char & at(int);                      // Subscript operator function
    const char & operator[] (int) const; // Constant subscript operator
    bool is_empty();                     // size == 0
    bool is_full();                      // size == capacity

    int get_size() const;                      // Returns size
    int length() const;                        // Alias for getsize()
    int get_capacity() const;                  // Returns capacity
    char * c_str() const;                      // Returns cstring

    void set(const string &);               // Alias - Copy assignment
    void set(const char *);                 // Alias - Parameterized assignment
    // bool insert(char, int);              // Positional insertion
    // bool insert(char);                   // Ordered insertion - push_back

    // bool remove();                       // Ordered deletion - pop_back
    // bool remove(int);                    // Positional deletion
    // bool remove(int, int);               // Positional deletion (multiple)
     
    // bool erase();                        // Removes all chars from the list.
};

// Helper functions
const int strlen(const char *);
// int strcmp(const string &, const string &);
// int strcpy(char *, const char *);

// Relational operators
bool operator == (const string &, const string &); 
bool operator != (const string &, const string &);
bool operator >  (const string &, const string &);
bool operator <  (const string &, const string &);
bool operator >= (const string &, const string &);
bool operator <= (const string &, const string &);

// Stream Operators
std::ostream & operator << (std::ostream &, const string &); 
std::istream & operator >> (std::istream &, string &);

