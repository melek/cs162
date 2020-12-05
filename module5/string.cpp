#include "string.h"

// Default constructor
string::string() {
     size           = 0;
     capacity       = 0;
     cstring          = nullptr;
}

// Copy constructor
string::string(const string & right) {
    size           = right.size;
    capacity       = right.capacity;
    cstring          = new char[capacity];
    for(auto i = 0; i < capacity; i++) 
         cstring[i]   = right[i];
}

// Parameterized copy constructor
string::string(const char * right) {
    size            = strlen(right);
    capacity        = size + 1;
    cstring           = new char[capacity];
    for(auto i = 0; i < capacity; i++)
        cstring[i]    = right[i];
}

// Move constructor 
string::string(string && right) {
    if(this != &right) {
        size        = right.size;
        capacity    = right.capacity;
        cstring       = right.cstring;
        right.size     = 0;
        right.capacity = 0;
        right.cstring    = nullptr;
    }
}

// Destructor
string::~string() {
    size     = 0;
    capacity = 0;
    if(cstring != nullptr) delete [] cstring;
}

// Copy assignment operator
string & string::operator = (const string & right) {
    if (this != &right) {
        size      = right.size;
        capacity  = right.capacity;
        if(cstring != nullptr) delete [] cstring;
        cstring = new char[capacity];
        for(auto i = 0; i < capacity; i++)
            cstring[i] = right[i];
    }
    return *this;
}

// Parameterized copy assignment operator
string & string::operator = (const char * right) {
    size        = strlen(right);
    capacity    = size + 1;
    if(cstring != nullptr) delete [] cstring;
    cstring       = new char[capacity];
    for(auto i = 0; i < capacity; i++)
        cstring[i] = right[i];
    return *this;
}

// Move assignment operator
string & string::operator = (string && right) {     
    if (this != &right) {
        size      = right.size;
        capacity  = right.capacity;
        if(cstring != nullptr) delete [] cstring;
        cstring           = right.cstring;
        right.size      = 0;
        right.capacity  = 0;
        right.cstring     = nullptr;
    }
    return *this;
}

// Subscript operators
char & string::operator [] (int position) {
    if (position <= 0)    return cstring[0];
    if (position >= size) return cstring[size];
    return cstring[position];
}

char & string::at(int position){
    return (*this)[position];
}

const char & string::operator [] (int position) const {
    return (*this)[position];
    // if (position <= 0)    return cstring[0];
    // if (position >= size) return cstring[size];
    // return cstring[position];
}

// Size & Capacity checkers
bool string::is_empty() {
    return size == 0;
}

bool string::is_full() {
    return (size + 1) == capacity;
}

// Getters
int string::get_size() const {
    return size;
}

int string::length() const {
    return size;
}

int string::get_capacity() const {
    return capacity;
}

char * string::c_str() const {
    return cstring;
}

// Setters
void string::set(const string & right) {
    *this = right;
}

void string::set(const char * right) {
    *this = right;
}

// Helper functions
const int strlen(const char * cstring) {
    int i = 0;
    while(cstring[i] != '\0') i++;
    return i;
}

// Core relational operators
bool operator == (const string & left, const string & right)
{   
    int ls = left.length();
    int rs = right.length();

    if(ls != rs) return false;

    for(int i = 0; i < ls; i++)
        if(left[i] != right[i]) return false;
    
    return true; 
}

bool operator >  (const string & left, const string & right)
{   
    // Our greater-than logic assumes A > z.
    int ls = left.length();
    int rs = right.length();

    // Find the smaller size to avoid accessing invalid indexes.
    int min = ls;
    if(ls > rs) min = rs;

    // The first character with a lower ASCII value is 'greatest'
    // This is because A is 'lower' than Z in ascii value.
    for(int i = 0; i < min; i++) {
        if(left[i] < right[i]) return true;
        if(left[i] > right[i]) return false;
    }
    // If they are equal, then the shorter string is 'greater'
    return ls <= rs; 
}

// Derived relational operators
bool operator != (const string & left, const string & right) { return !(left == right); }
bool operator <  (const string & left, const string & right) { return   left != right && !(left > right); }
bool operator >= (const string & left, const string & right) { return !(left <  right); }
bool operator <= (const string & left, const string & right) { return !(left >  right); }

// Stream operators
std::ostream & operator << (std::ostream & out, const string & right)
{
    out << right.c_str(); 
    return out;
}

std::istream & operator >> (std::istream & in, string & right)
{
    int size = 0;
    int capacity = 20;
    char * input = new char[capacity];
    for(int j = 0; j < capacity; j++) input[j] = '\0';
    char c;
    while(in.good() == true && in.peek() != '\n' && in.peek() > ' ') {
        if(size >= capacity) {
            capacity += STRING_H_CHUNK;
            char * temp = new char[capacity];
            for(int i = 0; i < capacity; i++) {
                if(i < size) temp[i] = input[i];
                else temp[i] = '\0';
            }
            delete [] input;
            input = temp;
        }
        in >> c;
        if(in.good()) input[size++] = c;
    }
    right = input;
    delete [] input;   
    return in;
}

