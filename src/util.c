#include <stdio.h>

#include "../includes/util.h"

/**
 * function safe_malloc
 * 
 * Regular malloc call with error check. To be used in the whole project
 * 
 * @param size_t The amount of bytes that we want to allocate
 * 
 * @return void* A pointer to the newly created memory
 */
void *safe_malloc(size_t bytes) {
    void *buffer = malloc(bytes);
    if(buffer == NULL) {
        printf("[Safe_Malloc]: Malloc has failed on file: %s:%d\n", __FILE__, __LINE__);
    }

    return buffer;
}

/**
 * function is_digit
 * 
 * @param char Character that we want to check
 * 
 * @return boolean whether or not the character is a digit
 */ 
bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

/**
 * function is_character_range_character
 * 
 * A character range character is either a letter (uppercase or lowercase) or a digit
 * 
 * @param char Character that we want to check
 * 
 * @return boolean whether or not the character is a range character
 */ 
bool is_character_range_character(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

/**
 * function is_character_class_character
 * 
 * A character range character is either a letter (uppercase or lowercase), a digit, or _, -
 * 
 * @param char Character that we want to check
 * 
 * @return boolean whether or not the character is a character class character
 */ 
bool is_character_class_character(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-' || c == '_';
}