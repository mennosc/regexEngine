#ifndef TOKEN_H
#define TOKEN_H

#include "list.h"

//Contains all different token types
enum TokenType {
    RANGEQUANTIFIER,
    CHARACTER_CLASS,
    CHARACTER_RANGE,
};

//Looks like {a,b}, {a,} or {a}
struct CharacterRange {
    char first;
    char last;
};

//Looks like [a-zA-Z0-9-_] or [abcA-Z]
struct CharacterClass {
    struct List *character_ranges;
    char *characters;
};

/** 
 * Structure for a token. The reason for using unions is so that there is 
 * only struct type (of type Token), that can represent all different kind of tokens
 * and the parameters that are needed for a specific token. This makes creating and
 * traversing the ast easier.

*/
struct Token {
    enum TokenType type;
    union {
        struct RangeQuantifier *range_quantifier_data;
        struct CharacterClass *character_class_data;
        struct CharacterRange *character_range_data;
    };
    struct Token *next;
};

//Function declarations
struct Token *create_range_quantifier(int num1, int num2);
struct Token *create_character_class(struct List *ranges, char *characters);
struct Token *create_character_range(char first, char second);

#endif