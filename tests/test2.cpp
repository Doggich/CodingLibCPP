#include <../source/codingLib.h>
#include <iostream>
#include <fstream>
#include <string>

void writeFile(const char* input, const char* path)  
{
    std::ofstream out(path);

    if (out.is_open()) 
    {
        out << input << std::endl;
        out.close();
        std::cout << "File written successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Error: Could not open file for writing!" << std::endl;
    }
}


int main()
{

    std::string input;
    std::cout << "Enter text: ";
    std::getline(std::cin, input);

    const char* encoded = encode_string(input.c_str());

    writeFile(encoded, "./output/output.txt");

    return 0;
}
