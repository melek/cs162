#include "Keyword.h"

// Default Constructor
Keyword::Keyword() {
    word            = "";
    count           = 0;
    lines           = nullptr;
    lines_size      = 0;
    lines_capacity  = 0;
}

// Copy Constructor
Keyword::Keyword(const Keyword & src) {
    word            = src.word;
    count           = src.count;
    lines_size      = src.lines_size;
    lines_capacity  = src.lines_capacity;
    lines = new int[lines_capacity];
    for(int i = 0; i < lines_capacity; ++i) lines[i] = src.lines[i];
}

// Conversion Constructor
Keyword::Keyword(string newWord) {
    word            = newWord;
    count           = 0;
    lines           = nullptr;
    lines_size      = 0;
    lines_capacity  = 0;
}

// Conversion Constructor + Addline
Keyword::Keyword(string newWord, int lineFound) {
    word            = newWord;
    count           = 0;
    lines_size      = 0;
    lines_capacity  = KEYWORD_H_CHUNK;
    lines           = new int[lines_capacity];
    for(int i = 0; i < lines_capacity; ++i) lines[i] = 0;
    addLine(lineFound);
}

Keyword::~Keyword() {
    if(lines != nullptr) delete [] lines;
}

// Copy assignment
Keyword & Keyword::operator = (const Keyword & right) {
    if(this != &right) {
        word            = right.word;
        count           = right.count;       
        lines_size      = right.lines_size;
        lines_capacity  = right.lines_capacity;
        if(lines != nullptr) delete [] lines;
        lines           = new int[lines_capacity];
        for(int i = 0; i < lines_capacity; ++i) lines[i] = right.lines[i];
    }
    return *this;
}

// Move assignment
Keyword & Keyword::operator = (Keyword && right) {
    if(this != &right) {
        word                 = right.word;
        count                = right.count;
        lines_size           = right.lines_size;
        lines_capacity       = right.lines_capacity;
        if(lines != nullptr) delete [] lines;
        lines                = right.lines; // Takeover source's lines array.

        // Clear the source variable.
        right.word           = "";
        right.count          = 0;
        right.lines          = nullptr;
        right.lines_size     = 0;
        right.lines_capacity = 0; 
    }
   return *this;
} 

char & Keyword::operator [] (int position) {
    return word[position];
}

const char & Keyword::operator [] (int position) const {
    return word[position];
}

int Keyword::addLine(int newLineFound) {
    // No matter what, we add to the word's count.
    ++count;

    // Return -1 if the line exists.
    for(int i = 0; i < lines_size; ++i)
        if(lines[i] == newLineFound)
            return SUCCESS_COUNT_ONLY;

    // Resize lines array if the capacity is full
    if(lines_size >= lines_capacity) {
        int * temp = new int[lines_capacity + KEYWORD_H_CHUNK];
        lines_capacity += KEYWORD_H_CHUNK;
        for(int i = 0; i < lines_capacity; ++i) 
            if(i < lines_size)
                temp[i] = lines[i];
            else
                temp[i] = 0;
        if(lines != nullptr) delete [] lines;
        lines = temp;        
    }

    // Add the new line
    lines[lines_size++] = newLineFound;
    return SUCCESS_LINE_ADDED;
}

string Keyword::get_word()      const { return word;            }
int    Keyword::get_count()     const { return count;           }
int    Keyword::get_ls()        const { return lines_size;      }
int    Keyword::get_lc()        const { return lines_capacity;  }
int *  Keyword::get_lines()     const { return lines;           }
int    Keyword::get_line(int l) const { return lines[l];        }

void Keyword::print(int prefix) {
    std::cout << prefix << ". \"" << word   << "\" occurs on lines ";   
    for(int i = 0; i < lines_size; ++i)
        std::cout       << lines[i] << " ";    
    std::cout << std::endl;
}

// Equality operator simply compares whether the strings are equal.
bool operator == (const Keyword & left, const Keyword & right) {
    return left.get_word() == right.get_word();
}

// Similarly, we are only comparing the actual word, not any count data. 
bool operator >  (const Keyword & left, const Keyword & right) {
    return left.get_word() > right.get_word();
}

// Derived relational operators
bool operator != (const Keyword & left, const Keyword & right) { return !(left == right); }
bool operator <  (const Keyword & left, const Keyword & right) { return !(left == right) && !(left > right); }
bool operator >= (const Keyword & left, const Keyword & right) { return !(left <  right); }
bool operator <= (const Keyword & left, const Keyword & right) { return !(left >  right); }

std::ostream & operator << (std::ostream & out, const Keyword & right) {
    out << "\"" << right.get_word() << "\": Found " << right.get_count();
    if(right.get_ls() > 0) {
        out << " on line";
        if(right.get_ls() > 1) out << "s";
        out << " ";
        for(int i = 0; i < right.get_ls(); ++i) {
            out << right.get_line(i);
            if( i < (right.get_ls() - 1)) out << ", ";
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
