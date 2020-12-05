#include "main.h"

int main(int argc, char **argv, char **envp)
{
     list           index;                   // Keyword index
     unsigned int   line = 1;                // Current line
     char      *    input = nullptr;         // Input buffer
     word      *    buffer;                  // Typed input buffers
     bool           word_in_progress = false;// Word parser
     char           byte = '\0';             // Input buffer for char

     while(std::cin.good() == true && std::cin.peek() != EOF)
     {
          input     = new char[2048];                                 // Input buffer
          for (auto idx = 0; idx < 2048; idx++) input[idx] = '\0';    // Create null string

          word_in_progress = false;                                   // Not parsing a word
          for(auto ptr = 0; ptr < 2047; ) {
               byte = std::cin.get();                                 // Read a byte
               if (std::cin.good() != true) break;                    // Stop on error
               if (byte <= ' ' || byte >= '~') {                      // Whitespace?
                    if (word_in_progress == true) {                   // If word in progress then we're at the end of the word
                        break;                                        // Done reading a word
                    } else {
                         if (byte == '\n') line++;                    // Update line
               }
               } else {                                               // Not whitespace
                    input[ptr++] = byte;                              // Add byte to the word
                    word_in_progress = true;                          // Make sure to note we're parsing a word
               }
          }

          if (std::cin.good() != true) continue;                      // Error?
          buffer = new word(input);                                   // Create proper data structure for list
          index.insert(buffer);                                       // Insert the word into the list
          index.data[index.find(buffer)].add_line(line);              // Add the line number
          if (byte  == '\n') line++;                                  // Incremenet line number
          delete [] input;                                            // Clean buffer
          delete buffer;                                              // Clean buffer
          buffer = nullptr;
          input = nullptr;
     }
     if (buffer != nullptr) delete buffer;
     if (input != nullptr) delete input;

     std::cout      << "Index: " << std::endl;
     for (auto idx = 0; idx < index.size; idx++)
     {
          std::cout      << idx << ". "
                         << "\"" << index.data[idx].data << "\""
                         << " occurs  on lines "
          ;
          for (auto lne = 0; lne < index.data[idx].size; lne++)
          {
               std::cout << index.data[idx].lines[lne] << " ";
          }
          std::cout << std::endl;
     }
     return 0;
}
