#include "KeywordIndex.h"
#include "Keyword.h"
#include <string>

#define NOT_FOUND   -1
#define CAP_STEP    5

KeywordIndex::KeywordIndex() {
    size = 0;
    capacity = CAP_STEP;
    words = new Keyword[capacity];
}

KeywordIndex::KeywordIndex(KeywordIndex & src) {
    size = src.size;
    capacity = src.capacity;
    words = new Keyword[capacity];
    for(int i = 0; i < size; i++) words[i] = src.words[i];
}

KeywordIndex & KeywordIndex::operator = (const KeywordIndex & right) {
    if(this == &right) return *this;
    size = right.size;
    capacity = right.capacity;
    if(words != nullptr) delete [] words;
    words = new Keyword[capacity];
    for(int i = 0; i < size; i++) words[i] = right.words[i];
    return *this;
}

KeywordIndex & KeywordIndex::operator = (KeywordIndex && right) {
    if(this == &right) return *this;
    size = right.size;
    capacity = right.capacity;
    if(words != nullptr) delete [] words;
    words = new Keyword[capacity];
    for(int i = 0; i < size; i++) words[i] = right.words[i];
    return *this;
}

int KeywordIndex::find(std::string word) {
    for(int i = 0; i < size; i++)
        if(words[i] == word) return i;
    return NOT_FOUND;
}

void KeywordIndex::grow() {
    capacity += CAP_STEP;
    Keyword * tempWords = new Keyword[capacity];
    for(int i = 0; i < size; i++) tempWords[i] = words[i];
    if(words != nullptr) delete [] words;
    words = tempWords;
}

void KeywordIndex::insert(std::string word, int lineNum) {
    int wordIndex = find(word);
    if(wordIndex == NOT_FOUND) {
        // New Keyword, add it to the array.
        if(size == capacity) grow();
        words[size++] = Keyword(word, lineNum);
    }
    else {
        // Add count to existing Keyword.
        words[wordIndex].addLine(lineNum);
    }
}

void KeywordIndex::sort() {
    bool isSorted = true;
    Keyword heldWord;
    for(int i = 0; i < (size - 1); ++i) {
        heldWord = words[i];
        if(heldWord > words[i + 1]) {
            isSorted = false;
            words[i]    = words[i + 1];
            words[i + 1]  = heldWord;
        }
    }
    if(!isSorted) sort();
}

std::ostream & operator << (std::ostream & out, const KeywordIndex & right) {
    for(int i = 0; i < right.size; ++i)
        out << i + 1 << ". " << right.words[i]; 
    return out;
}

std::istream & operator >> (std::istream & in, KeywordIndex & right) {
    std::string inputWord;
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
