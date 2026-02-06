#include <../source/codingLib.h>
#include <iostream>
#include <string>

int main()
{

    const char* encoded = encode_string("Hello, world!");
    std::cout << "Encoded: " << encoded << std::endl;
    
    const char* decoded = decode_string(encoded);
    std::cout << "Decoded: " << decoded << std::endl;

    return 0;
}
