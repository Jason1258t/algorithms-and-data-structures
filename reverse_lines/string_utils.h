#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cstddef> 

size_t stringLength(const char *str);
void stringCopy(char *dest, const char *src);
bool isLineEnding(char c);
void reverseString(char str[]);

#endif 