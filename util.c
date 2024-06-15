#include <stdio.h>

#include "util.h"

void *safe_malloc(size_t bytes) {
    void *buffer = malloc(bytes);
    if(buffer == NULL) {
        printf("[Safe_Malloc]: Malloc has failed on file: %s:%d\n", __FILE__, __LINE__);
    }

    return buffer;
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_character_range_character(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

bool is_character_class_character(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-' || c == '_';
}