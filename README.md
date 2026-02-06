# Coding Library DLL

## Overview

This library provides functions for encoding and decoding text to/from a binary format. Each character is encoded into an 8-bit sequence, supporting a comprehensive set of alphanumeric characters, punctuation, and special symbols.

## Features
1. Encode strings to 8-bit binary format
2. Decode binary strings back to text
3. Support for 79 different characters:
    * Lowercase letters (a-z)
    * Uppercase letters (A-Z)
    * Digits (0-9)
    * Spaces and tabs
    * Punctuation and special symbols
    * Brackets and mathematical operators
4. Cross-platform compatibility (Windows, Linux, macOS)
5. C-compatible API for use with other programming languages

## API Reference

### C++ Functions

```cpp
std::string encode(std::string decode_str);
```

Encodes a text string into binary format.

#### Parameters:

* decode_str: Input string to encode

#### Returns:

* Binary string (8 bits per character)

#### Throws:

* std::runtime_error if an unsupported character is encountered

```cpp
std::string decode(std::string encode_str);
```

Decodes a binary string back to text.

#### Parameters:

* encode_str: Binary string to decode (must be divisible by 8)

#### Returns:

* Decoded text string

> __Note__: unrecognized binary sequences are replaced with '?'

### C API (For FFI/Shared Library)

```c
const char* encode_string(const char* input);
```

C-compatible encoding function.

```c
const char* decode_string(const char* input);
```

C-compatible decoding function.

> __Note__: these functions return pointers to static buffers. For thread-safe usage, create appropriate wrappers.

## Usage Examples

### C++ Usage

```cpp
#include <../source/codingLib.h>
#include <iostream>

int main() {
    // Encoding example
    std::string original = "Hello, World!";
    std::string encoded = encode(original);
    std::cout << "Encoded: " << encoded << std::endl;
    
    // Decoding example
    std::string decoded = decode(encoded);
    std::cout << "Decoded: " << decoded << std::endl;
    
    return 0;
}
```

### Using the Shared Library (Python with ctypes)

```python
import ctypes

# Load the shared library
encoder = ctypes.CDLL('./libencoder.so')  # or encoder.dll on Windows

# Define function signatures
encoder.encode_string.argtypes = [ctypes.c_char_p]
encoder.encode_string.restype = ctypes.c_char_p
encoder.decode_string.argtypes = [ctypes.c_char_p]
encoder.decode_string.restype = ctypes.c_char_p

# Use the functions
encoded = encoder.encode_string(b"Hello!")
print(f"Encoded: {encoded.decode('utf-8')}")

decoded = encoder.decode_string(encoded)
print(f"Decoded: {decoded.decode('utf-8')}")
```

### Using the Shared Library (C)

```c
#include <../source/codingLib.h>
#include <stdio.h>

// Declare the external functions
extern const char* encode_string(const char* input);
extern const char* decode_string(const char* input);

int main() {
    const char* text = "Test 123";
    const char* encoded = encode_string(text);
    printf("Encoded: %s\n", encoded);
    
    const char* decoded = decode_string(encoded);
    printf("Decoded: %s\n", decoded);
    
    return 0;
}
```

## Building the Library

### As a Shared Library

#### Windows:

```bash
g++ -shared -o coding.dll "source/codingLib.cpp" -std=c++11
```

#### Linux/macOS:

```bash
g++ -shared -o coding.dll "source/codingLib.cpp" -std=c++11 -fPIC
```

### Static Library

```bash
# Create object file
g++ <file.cpp> ..\source\codingLib.cpp -I "../source" -o <file.exe>
```

## Encoding Scheme

```text
------------------------
Binary Code  | Character
-------------|----------
00000000     | a
------------------------
00000001     | b
------------------------
00000010     | c
------------------------
00000011     | d
------------------------
00000100     | e
------------------------
00000101     | f
------------------------
00000110     | g
------------------------
00000111     | h
------------------------
00001000     | i
------------------------
00001001     | j
------------------------
00001010     | k
------------------------
00001011     | l
------------------------
00001100     | m
------------------------
00001101     | n
------------------------
00001110     | o
------------------------
00001111     | p
------------------------
00010000     | q
------------------------
00010001     | r
------------------------
00010010     | s
------------------------
00010011     | t
------------------------
00010100     | u
------------------------
00010101     | v
------------------------
00010110     | w
------------------------
00010111     | x
------------------------
00011000     | y
------------------------
00011001     | z
------------------------
00011010     | A
------------------------
00011011     | B
------------------------
00011100     | C
------------------------
00011101     | D
------------------------
00011110     | E
------------------------
00011111     | F
------------------------
00100000     | G
------------------------
00100001     | H
------------------------
00100010     | I
------------------------
00100011     | J
------------------------
00100100     | K
------------------------
00100101     | L
------------------------
00100110     | M
------------------------
00100111     | N
------------------------
00101000     | O
------------------------
00101001     | P
------------------------
00101010     | Q
------------------------
00101011     | R
------------------------
00101100     | S
------------------------
00101101     | T
------------------------
00101110     | U
------------------------
00101111     | V
------------------------
00110000     | W
------------------------
00110001     | X
------------------------
00110010     | Y
------------------------
00110011     | Z
------------------------
00110100     | 0
------------------------
00110101     | 1
------------------------
00110110     | 2
------------------------
00110111     | 3
------------------------
00111000     | 4
------------------------
00111001     | 5
------------------------
00111010     | 6
------------------------
00111011     | 7
------------------------
00111100     | 8
------------------------
00111101     | 9
------------------------
00111110     | (space)
------------------------
00111111     | ,
------------------------
01000000     | .
------------------------
01000001     | (
------------------------
01000010     | )
------------------------
01000011     | {
------------------------
01000100     | }
------------------------
01000101     | [
------------------------
01000110     | ]
------------------------
01000111     | -
------------------------
01001000     | =
------------------------
01001001     | _
------------------------
01001010     | +
------------------------
01001011     | <
------------------------
01001100     | >
------------------------
01001101     | /
------------------------
01001110     | |
------------------------
01001111     | \
------------------------
01010000     | ?
------------------------
01010001     | !
------------------------
01010010     | (tab)
------------------------
01010011     | (newline)
------------------------
```

## Error Handling

### Encoding Errors

* Throws `std::runtime_error` when encountering unsupported characters
* C API returns "ERROR" string on failure

### Decoding Issues

* Invalid input (non-binary characters) may cause undefined behavior
* Binary strings not divisible by 8 will be partially processed
* Unknown 8-bit sequences are replaced with '?'

### Limitations

1. Input for decoding must contain only '0' and '1' characters
2. Binary string length must be a multiple of 8
3. Limited character set (79 supported characters)
4. C API uses static buffers (not thread-safe by default)

## Performance Notes
* Encoding/decoding complexity: O(n)
* Memory usage: ~8x expansion when encoding (text → binary)
* Fixed lookup tables provide constant-time character mapping

## Testing

```cpp
#include <iostream>
#include <cassert>

int main() {
    // Test round-trip
    std::string test = "Hello World 123!";
    std::string encoded = encode(test);
    std::string decoded = decode(encoded);
    
    assert(test == decoded);
    std::cout << "Test passed!" << std::endl;
    
    return 0;
}
```
## Author
[Doggich](https://github.com/Doggich)
