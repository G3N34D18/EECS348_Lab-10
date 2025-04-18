#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "calculator.hpp"

int main(int argc, char *argv[]) {
    // verify correct inputs to main function 
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    // open file
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << argv[1] << std::endl;
        return 1;
    }
    // line is of type string
    std::string line;
    // while there are lines in the file
    while (std::getline(file, line))
    {   
        // erases blank space for proper analysis
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        // verifies double
        if (isValidDouble(line))
        {
            // does required addition with specified value
            std::string returnVal = add(line, "-123.456");
            std::cout << "Sum of " << line << " and -123.456 is " << returnVal << std::endl;
        }
        // if not valid double then returns invalidity 
        else
        {
            std::cout << "Line: " << line << " is an invalid double value." << std::endl;
        }
        // closes file
    }
    file.close();
    return 0;
}
