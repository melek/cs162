#pragma once
#include "Keyword.h"

#define KEYWORDINDEX_H_CHUNK    5
#define NOT_FOUND               -1

class KeywordIndex {
  private:
    Keyword * words;
    int size;
    int capacity;
    void grow();                        // Grows the capacity

  public:
    KeywordIndex();                     // Default Constructor
    KeywordIndex(const KeywordIndex &); // Copy Constructor
    KeywordIndex(KeywordIndex &&);      // Move Constructor
    ~KeywordIndex();                    // Destructor

    KeywordIndex & operator = (const KeywordIndex &); // Copy Assignment
    KeywordIndex & operator = (KeywordIndex &&);      // Move Assignment

    Keyword & operator [] (int);              // Subscript 
    const Keyword & operator [] (int) const;  // Const Subscript

    int get_size() const;    
    int find(string) const;
    void insert(string, int);
};

bool operator == (const KeywordIndex &, const KeywordIndex &);
bool operator >  (const KeywordIndex &, const KeywordIndex &);
bool operator != (const KeywordIndex &, const KeywordIndex &);
bool operator <  (const KeywordIndex &, const KeywordIndex &);
bool operator >= (const KeywordIndex &, const KeywordIndex &);
bool operator <= (const KeywordIndex &, const KeywordIndex &);

std::ostream & operator << (std::ostream &, const KeywordIndex &);  // Stream insertion
std::istream & operator >> (std::istream &, KeywordIndex &);        // Stream extraction
