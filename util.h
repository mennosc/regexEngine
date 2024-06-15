#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdbool.h>

void *safe_malloc(size_t bytes);

bool is_digit(char c);
bool is_character_class_character(char c);
bool is_character_range_character(char c);

#endif //UTIL_H