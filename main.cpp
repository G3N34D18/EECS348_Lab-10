#include <iostream>
#include <fstream>
#include <string>

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
    std::string line;
    while (std::getline(file, line))
    {
        if (isValidDouble(line))
        {
            std::string returnVal = add(line, "-123.456");
            std::cout << "Sum of " << line << " and -123.456 is " << returnVal << std::endl;
        }
        else
        {
            std::cout << "Line: " << line << " is an invalid double value." << std::endl;
        }
        file.close();
        return 0;
    }

}
