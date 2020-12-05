#include "KeywordIndex.h"

// Default Constructor
KeywordIndex::KeywordIndex() {
    size = 0;
    capacity = KEYWORDINDEX_H_CHUNK;
    words = new Keyword[capacity];
}

// Copy Constructor
KeywordIndex::KeywordIndex(const KeywordIndex & src) {
    size = src.size;
    capacity = src.capacity;
    words = new Keyword[capacity];
    for(int i = 0; i < size; i++) words[i] = src.words[i];
}

// Move Constructor 
KeywordIndex::KeywordIndex(KeywordIndex && src) {
    size         = src.size;
    capacity     = src.capacity;
    words        = src.words;

    // Clear source variable
    src.size     = 0;
    src.capacity = 0;
    src.words    = nullptr;
}

KeywordIndex::~KeywordIndex() {
    size        = 0;
    capacity    = 0;
    if(words != nullptr) {
        delete [] words;
        words   = nullptr;
    }
}

// Copy Assignment
KeywordIndex & KeywordIndex::operator = (const KeywordIndex & right) {
    if(this != &right) {
        size     = right.size;
        capacity = right.capacity;
        if(words != nullptr) delete [] words;
        words = new Keyword[capacity];
        for(int i = 0; i < size; i++) words[i] = right.words[i];
    }
    return *this;
}

// Move Assignment
KeywordIndex & KeywordIndex::operator = (KeywordIndex && right) {
    if(this != &right) {
        size            = right.size;
        capacity        = right.capacity;
        if(words != nullptr) delete [] words;
        words           = right.words;

        // Clear source variable
        right.size      = 0;
        right.capacity  = 0;
        right.words     = nullptr;
    }
    return *this;
}

Keyword & KeywordIndex::operator [] (int position) {
    return words[position];
}

const Keyword & KeywordIndex::operator [] (int position) const {
    return words[position];
}

int KeywordIndex::get_size() const {
    return size;
}

int KeywordIndex::find(string word) const {
    for(int i = 0; i < size; i++)
        if(words[i] == word) return i;
    return NOT_FOUND;
}

void KeywordIndex::grow() {
    // Only grow if needed.
    if(size < capacity) return;

    // Add to capacity and transfer our words array.
    capacity += KEYWORDINDEX_H_CHUNK;
    Keyword * tempWords = new Keyword[capacity];
    for(int i = 0; i < size; i++) tempWords[i] = words[i];
    if(words != nullptr) delete [] words;
    words = tempWords;
}

void KeywordIndex::insert(string word, int lineNum) {
    int wordIndex = find(word);
    if(wordIndex == NOT_FOUND) {
        // New Keyword, add it to the array.
        grow();
        int newWordIndex = 0;
        // Scan for the place the new word should go.
        for(;newWordIndex < size; ++newWordIndex)
            if(word > words[newWordIndex]) break;

        // Transfer our words to the right of target location.
        for(int i = size; i > newWordIndex; --i) 
            words[i] = words[i-1];

        // Set new word and increment size
        Keyword newKeyword(word, lineNum);
        words[newWordIndex] = newKeyword;
        ++size;
    }
    else {
        // Add count to existing Keyword.
        words[wordIndex].addLine(lineNum);
    }
}

// Equality operator simply compares whether the sizes are equal.
bool operator == (const KeywordIndex & left, const KeywordIndex & right) {
    return left.get_size() == right.get_size();
}

// Similarly, we are only comparing the sizes of the words arrays, not any string data. 
bool operator >  (const KeywordIndex & left, const KeywordIndex & right) {
    return left.get_size() > right.get_size();
}

// Derived relational operators
bool operator != (const KeywordIndex & left, const KeywordIndex & right) { return !(left == right); }
bool operator <  (const KeywordIndex & left, const KeywordIndex & right) { return !(left == right) && !(left > right); }
bool operator >= (const KeywordIndex & left, const KeywordIndex & right) { return !(left <  right); }
bool operator <= (const KeywordIndex & left, const KeywordIndex & right) { return !(left >  right); }

std::ostream & operator << (std::ostream & out, const KeywordIndex & right) {
    int rs = right.get_size();
    for(int i = 0; i < rs; ++i)
        out << i << ". " << right[i]; 
    return out;
}

std::istream & operator >> (std::istream & in, KeywordIndex & right) {
    string inputWord;
    int lineNum = 1;
    while(in.peek() != EOF && in.good()) {
        // Eat whitespace so we can count new lines.
        while(in.peek() == '\n' || in.peek() == '\t' || in.peek() == ' ') {
            if(in.peek() == '\n') ++lineNum;
            in.ignore(1);
        }
        in >> inputWord;
        if(in.good()) {
            right.insert(inputWord, lineNum);
        }
    }    
    return in;
}
