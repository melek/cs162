#pragma once
#include "Keyword.h"
#include <string>
#include <iostream>

struct KeywordIndex {
    Keyword * words;
    int size;
    int capacity;

    KeywordIndex();               // Default Constructor
    KeywordIndex(KeywordIndex &); // Copy Constructor

    KeywordIndex & operator = (const KeywordIndex &); // Copy Assignment
    KeywordIndex & operator = (KeywordIndex &&);      // Move Assignment
    
    int find(std::string);
    void grow();
    void insert(std::string, int);
    void sort();
};

std::ostream & operator << (std::ostream &, const KeywordIndex &);  // Stream insertion
std::istream & operator >> (std::istream &, KeywordIndex &);        // Stream extraction
