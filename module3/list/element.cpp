#include <iostream>
#include "element.h"

element::element() {
    data = 0;
}

element::element(const element & src) {
    data = src.data;
}

element::element(int val) {
    data = val;
}

element & element::operator = (const element & right) {
    if(this != &right)
        data = right.data;
    return *this;
}

element & element::operator = (element && right) {
    if(this != &right) {
        data = right.data;
        right.data = 0;
    }
    return *this;
}

element & element::operator = (int & right) {
    data = right;
    return *this;
}

bool operator == (element & left, element & right) {
    return (left.data == right.data);
}

bool operator != (element & left, element & right) {
    return (left.data != right.data);
}

bool operator > (element & left, element & right) {
    return (left.data > right.data);
}

std::ostream & operator << (std::ostream & out, const element & right) { 
    out << right.data;
    return out;
}

std::istream & operator >> (std::istream & in, element & right) {
    in >> right.data;
    return in;
}

