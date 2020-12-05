#include "list.h"

list::~list()
{
     if (data != nullptr) delete [] data;
}

list::list()
{
     data           = nullptr;
     capacity       = 0;
     size           = 0;
}

void list::insert(word * parm)
{
     bool           found     = false;
     int            position  = 0;

     if (size >= capacity)
     {
          word * temp = new word[capacity + 5];
          for(auto ptr = 0; ptr < size; ptr++) temp[ptr] = data[ptr];
          if (data != nullptr) delete [] data;
          data = temp;
          capacity += 5;
     }

     for(position = 0; position < size; position++)
     {
          if (data[position] == *parm) {
               found = true;
               break;
          }
          if (data[position] > *parm) {
               found = false;
               break;
          }
     }

     if (found == false) {
          if (size < capacity) {
               for(auto idx = size; idx > position; idx--)
               {
                    data[idx] = data[idx - 1];
                    data[idx - 1].erase();
               }
               data[position] = *parm;
               size++;
          }
     }
}

int list::find(word * target) {
     int       result = 0;
     for (result = 0; result < size; result++) {
          if (data[result] == *target) break;
     }
     return result;
}

