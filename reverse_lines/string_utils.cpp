#include <cstddef>
#include "string_utils.h"
#include <algorithm>

size_t stringLength(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

void stringCopy(char *dest, const char *src)
{
    size_t i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool isLineEnding(char c) {
    return c == '\n' || c == '\r';
}

void reverseString(char str[])
{
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    
    for (int i = 0; i < length / 2; i++) {
        std::swap(str[i], str[length - 1 - i]);
    }
}
