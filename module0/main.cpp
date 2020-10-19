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
        if(fileStream.fail()) {
            std::cout << "File access error: " 
                 << std::strerror(errno) 
                 << std::endl;
            return -1;
        }
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
    outputCount("Uppercase", countUpperA);
    outputCount("Lowercase", countLowerA);
    outputCount("Numbers", countNumber);
    outputCount("Whitespace", countWspace);

    return 0;
}

std::filebuf getFile() {
    std::filebuf file;
    std::string filename("");
    std::string error("");
    int nameLength;

    do {
        if(error.length() > 0) {
            std::cout << error << std::endl;
            error = "";
        }
        std::cout << "Please enter a filename: ";
        std::cin.clear();
        std::getline(std::cin, filename);

        // Check for invalid names.
        nameLength = filename.length();
        if(nameLength > 255) {
            error = "Oops! The filename is too long (255 character max).";
        } else if(nameLength == 0) {
            error = "You must provide a filename.";
        }

    } while(!file.open(filename, std::ios::in));
    
    return file;
}

void outputCount(std::string charType, int count) {
    std::cout << charType << ":\t" << count << std::endl;
} 
