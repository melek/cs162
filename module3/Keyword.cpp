#include "Keyword.h"
#include <string>
#include <iostream>

#define ERR_OUT_OF_LINES    -1
#define ERR_DUPLICATE_LINE  0
#define LINE_ADD_SUCCESS    1

Keyword::Keyword() {
    word = "";
    linesFound = 0;
    count = 0;
    for(int i = 0; i < MAXLINES; ++i) lines[i] = 0;
}

Keyword::Keyword(Keyword & src) {
    word        = src.word;
    linesFound  = src.linesFound;
    count       = src.count;
    for(int i = 0; i < MAXLINES; ++i) lines[i] = 0;
}

Keyword::Keyword(std::string newWord) {
    word = newWord;
    linesFound = 0;
    count = 0;
    for(int i = 0; i < MAXLINES; ++i) lines[i] = 0;
}

Keyword::Keyword(std::string newWord, int lineFound) {
    word = newWord;
    linesFound = 0;
    count = 0;
    for(int i = 0; i < MAXLINES; ++i) lines[i] = 0;
    addLine(lineFound);
}

Keyword & Keyword::operator = (const Keyword & right) {
    if(this != &right) {
        word        = right.word;
        linesFound  = right.linesFound;
        count       = right.count;       
        for(int i = 0; i < MAXLINES; ++i) lines[i] = right.lines[i];
    }
    return *this;
}

Keyword & Keyword::operator = (Keyword && right) {
    if(this != &right) {
        word        = right.word;
        linesFound  = right.linesFound;
        count       = right.count;
        for(int i = 0; i < MAXLINES; ++i) lines[i] = right.lines[i];
    }
   return *this;
} 

int Keyword::addLine(int newLineFound) {
    ++count;

    // Return non-success value if the capacity is full
    if(linesFound >= MAXLINES)
        return ERR_OUT_OF_LINES;

    // Return non-success value if the line exists
    for(int i = 0; i < linesFound; ++i)
        if(lines[i] == newLineFound) 
            return ERR_DUPLICATE_LINE;
    
    lines[linesFound++] = newLineFound;   
    return LINE_ADD_SUCCESS;
}

void Keyword::print(int prefix) {
    std::cout << prefix << ". \""
              << word << "\" occurs on lines ";
    for(int i = 0; i < linesFound; ++i)
        std::cout << lines[i] << " ";
    std::cout << std::endl;
}

// Equality operator simply compares whether the strings are equal.
bool operator == (const Keyword & left, const Keyword & right) {
    return (left.word == right.word);
}

// Similarly, we are only comparing the actual word, not any count data. 
bool operator >  (const Keyword & left, const Keyword & right) {
    return left.word > right.word;
}

std::ostream & operator << (std::ostream & out, const Keyword & right) {
    out << "'" << right.word << "': Found " << right.count;
    if(right.linesFound > 0) {
        out << " on line";
        if(right.linesFound > 1) out << "s";
        out << " ";
        for(int i = 0; i < right.linesFound; ++i) {
            out << right.lines[i];
            if( i < (right.linesFound - 1)) out << ", ";
        }
    }
    out << std::endl;
    return out;
}

// This implementation expects line numbers which a keyword was found on.
std::istream & operator >> (std::istream & in, Keyword & right) {
    int lineNum;
    in >> lineNum;
    right.addLine(lineNum);
    return in;
}
