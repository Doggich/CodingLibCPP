#ifndef MYLIB_H
#define MYLIB_H

#ifdef __cplusplus
extern "C" {
#endif

const char* encode_string(const char* input);
const char* decode_string(const char* input);
void free_string(char* str);

#ifdef __cplusplus
}
#endif

#endif