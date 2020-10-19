#include "main.h"

int main(int argc, char **args, char **envp) {
    // Step 0: Declare variables.
    std::filebuf file;
    int countUpperA = 0;
    int countLowerA = 0;
    int countNumber = 0;
    int countWspace = 0;

    // Step 1: Collect input.
    file = getFile();

    // Step 2: Iterate through our file and generate counts.
    char thisChar;
    std::istream fileStream(&file);
    while(fileStream) {
        thisChar = char(fileStream.get());
        if(isupper(thisChar)) {
            ++countUpperA;
        }
        else if(islower(thisChar)) {
            ++countLowerA;
        }
        else if(isdigit(thisChar)) {
            ++countNumber;
        }
        else if(isspace(thisChar)) {
            ++countWspace;
        }
    }

    // Step 3: Close the file
    file.close();

    // Step 4: Output our counts
    outputCount("Uppercase letters", countUpperA);
    outputCount("Lowercase letters", countLowerA);
    outputCount("Numbers", countNumber);
    outputCount("Whitespace", countWspace);

    return 0;
}

std::filebuf getFile() {
    std::filebuf file;
    string filename("");
    string error("");
    int nameLength;

    do {
        if(file.fail()) 
            cout << "File access error: " 
                 << strerror(errno) 
                 << std::endl;        
        if(error.length > 0) {
            std::cout << error << std::endl;
            error = "";
        }
        std::cout << "Please enter a filename: ";
        std::cin.clear();
        std::cin.getline(filename, 255);

        // Check for invalid names.
        nameLength = filename.length;
        if(nameLength > 255) {
            error = "Oops! The filename is too long (255 character max).";
        } else if(nameLength == 0) {
            error = "You must provide a filename.";
        }

    } while(!file.open(filename, std::ios::in));
    
    return file;
}

void outputCount(string charType, int count) {
    std::cout << charType << ":\t" << count << std::endl;
} 
