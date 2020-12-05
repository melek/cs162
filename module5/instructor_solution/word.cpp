#include "word.h"

word::~word()
{
     if (data != nullptr) delete [] data;
     if (lines != nullptr) delete [] lines;
     data           = nullptr;
     lines          = nullptr;
     size           = 0;
     capacity       = 0;
     
}

word::word()
{
     data           = nullptr;               // No c-string
     lines          = nullptr;               // No line array
     size           = 0;
     capacity       = 0;
}

word::word(char * c_string) : word::word()
{
     data           = new char[strlen(c_string) + 2];       // New C-string
     strcpy(data,c_string);                                 // Copy parm
}

void word::erase()
{
     if (data != nullptr) delete [] data;
     if (lines != nullptr) delete [] lines;
     data           = nullptr;
     lines          = nullptr;
     size = 0;
     capacity = 0;
}

void word::add_line(unsigned int target)
{
     int            position  = 0;
     bool           found     = false;

     // Increase the array size if necessary
     if (size >= capacity) {
          unsigned int * temp = new unsigned int [capacity + 5];
          for(auto ptr = 0; ptr < capacity + 5; ptr++) temp[ptr] = 0;
          if (lines != nullptr)
          {
               for (auto ptr = 0; ptr < size; ptr++) temp[ptr] = lines[ptr];
               delete [] lines;
          }
          lines = temp;
          capacity       += 5;
     }

     // Scan the array
     for(position = 0; position < size; position++)
     {
          if (lines[position] == target) {
               found = true;
               break;
          }
          if (lines[position] > target) {
               found = false;
               break;
          }
     }

     // Insert if necessary
     if (found == false)
     {
          for(auto idx = size; idx > position; idx--) lines[idx] = lines[idx - 1];
          lines[position] = target;
          size++;
     }
}

bool operator == (const word & left, const word & right)
{
     if (strcmp(left.data, right.data) == 0) return true;
     return false;
}

bool operator >  (const word & left, const word & right)
{
     if (strcmp(left.data, right.data) > 0) return true;
     return false;
}

word & word::operator = (const word & right)
{
     if (this != &right)
     {
          if (data != nullptr) delete [] data;
          if (lines != nullptr) delete [] lines;
          data = new char[strlen(right.data) + 2];
          strcpy(data,right.data);
          lines = new unsigned int[right.capacity];
          for(auto ptr = 0; ptr < right.capacity; ptr++) lines[ptr] = right.lines[ptr];
          size = right.size;
          capacity = right.capacity;
     }

     return *this;
}
