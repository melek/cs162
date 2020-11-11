#include "list.h"
#include "element.h"
#include <iostream>
#define CAP_CHUNK_SIZE 5

list::list() {
    size = 0;
    capacity = 0;
    data = nullptr;
}

list::list(const list & right) {
    size        = right.size;
    capacity    = right.capacity;
    data        = new element[capacity];
    for(int i = 0; i < size; i++) data[i] = right[i];
}

list & list::operator = (const list & right) {
    if(this != &right) {
        size        = right.size;
        capacity    = right.capacity;        
        data        = new element[capacity];
        for(int i = 0; i < size; i++) data[i] = right[i];
    }
    return *this;
}

list & list::operator = (list && right) {
    if(this != &right) {
        size        = right.size;
        capacity    = right.capacity;        
        data        = new element[capacity];
        for(int i = 0; i < size; i++) data[i] = right[i];
    }
    return *this;
}

void list::insert(element newItem) {
    if(size == capacity)
        capacity += CAP_CHUNK_SIZE;    
    element * tempData = new element[capacity];
    for(int i = 0; i < size; i++) {
        tempData[i] = data[i];
    }
    tempData[size] = newItem;

    if(data != nullptr) delete [] data;
    data = tempData;
    size++;
}

void list::insert(int newItemInt) {
    element newItem;
    newItem = newItemInt;
    insert(newItem);
}

void list::remove(element refItem) {
    int count = find(refItem);
    if(count == 0) return;    
    
    // If we can, shrink our array capacity by a factor of CAP_CHUNK_SIZE.
    int newSize = size - count;    
    if((capacity - newSize) >= CAP_CHUNK_SIZE)
        capacity = CAP_CHUNK_SIZE * ((newSize / CAP_CHUNK_SIZE) + 1);
     
    int numRemoved = 0;
    element * tempData = new element[capacity];

    for(int i = 0; count != numRemoved && i < size; i++) {
        if(data[i] != refItem) 
            tempData[i-numRemoved] = data[i];
        else 
            ++numRemoved;
    }

    data = tempData;
    size = size - count;
}

void list::remove(int refItemInt) {
    element refItem = refItemInt;
    remove(refItem);
}

const element & list::at(int index) {
    // Strict indexing; end the program if given an invalid index
    if(0 <= index && index <= size) 
        return data[index];
    std::cout << "list::at(int): Array index out of range." << std::endl;
    exit(1);
}

element & list::operator [] (int index) {
    // Strict indexing; end the program if given an invalid index
    if(0 <= index && index <= size) 
        return data[index];
    std::cout << "list::at(int): Array index out of range." << std::endl;
    exit(1);
}

const element & list::operator [] (int index) const { 
    // Strict indexing; end the program if given an invalid index
    if(0 <= index && index <= size) 
        return data[index];
    std::cout << "list::at(int): Array index out of range." << std::endl;
    exit(1);
}

int list::length() {
    return size;
}

int list::find(element refItem) {
    int count = 0;
    for(int i = 0; i < size; ++i) 
        if(data[i] == refItem) ++count;
    return count;
}

int list::find(int refItemInt) {
    element refItem = refItemInt;
    return find(refItem);
}

bool operator == (const list & left, const list & right) {
    return (left.size == right.size);
}

bool operator >  (const list & left, const list & right) {
    return (left.size > right.size);
}

std::ostream & operator << (std::ostream & out, const list & right) {
    for(int i = 0; i < right.size; i++) out << right.data[i] << " ";
    return out;
}

std::istream & operator >> (std::istream & in, list & right) {
    element input;
    while (in.peek() != EOF && in.peek() != '\n' && in.good()) {
        in >> input;
        if(in.good() == true) right.insert(input);
    }
    return in;
}

