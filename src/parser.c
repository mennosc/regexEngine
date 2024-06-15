#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/parser.h"
#include "../includes/util.h"
#include "../includes/token.h"


/**
 * function create_parser
 * 
 * @param source: The regular expression that we want to parse
 * 
 * @return struct Parser *: A pointer to the newly created Parser structure. 
 */
struct Parser *create_parser(char *source) {
    struct Parser *parser = safe_malloc(sizeof(struct Parser));
    parser->source_length = strlen(source);
    parser->current_index = 0;
    parser->current_character = source[parser->current_index];
    parser->source = strdup(source);
    
    return parser;
}

/**
 * Function parse_advance
 * 
 * @param parser A pointer to a Parser structure containing the source string and the current parsing state.
 * 
 * @return void
 */
void parser_advance(struct Parser *parser) {
    if(parser->current_index > parser->source_length - 1) {
        printf("You have reached the end of the input. Can't advance any further. At %s:%d\n", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    parser->current_index++;
    parser->current_character = parser->source[parser->current_index];
}

/**
 *  Function parse_number
 * 
 *   Only parses positive numbers since negative numbers do not occur in regular expressions
 * 
 *   @param Parser A pointer to a Parser structure containing the source string and the current parsing state.
 *   @param value A pointer to an integer that stores the parsed number;
 *   @returns The parsed number as an integer. If no valid integer is found, the function returns NULL
 */
bool parse_number(struct Parser *parser, int *value) {
    if(!is_digit(parser->current_character)) {
        return false;
    }

    int result = 0;
    while(is_digit(parser->current_character) && parser->current_character != '\0') {
        result = result * 10 + (parser->current_character - '0');
        parser_advance(parser);
    }

    *value = result;
    return true;
}

/**
 * Function parse_symbol
 * 
 * @param Parser A pointer to a Parser structure containing the source string and the current parsing state.
 * 
 * @return boolean denoting whether or not the parser matched a particular symbol
 */
bool parse_symbol(struct Parser *parser, char symbol) {
    if(parser->current_character == symbol) {
        parser_advance(parser);
        return true;
    }

    return false;
}

/**
 * Function parse_character_range_character
 * 
 * @param parser A pointer to a Parser structure containing the source string and the current parsing state.
 * @param value A pointer to a character that will store the range character
 * 
 * @return boolean whether or not the current character is a range character
 */
bool parse_character_range_character(struct Parser *parser, char *value) {
    if(is_character_range_character(parser->current_character)) {
        *value = parser->current_character;
        parser_advance(parser);
        return true;
    }

    return false;
}

/**
 * Function parser_peek
 * 
 * @param parser A pointer to a Parser structure containing the source string and the current parsing state
 * @param offset Amount of characters that we want to see past the current character
 * 
 * @return The character that is 'offset' characters ahead of the current characters. Returns -1 if the user tries to peek out of bounds 
 */
char parser_peek(struct Parser *parser, size_t offset) {
    if(parser->current_index + offset < parser->source_length) {
        return parser->source[parser->current_index + offset];
    }
    return -1;
}

/**
 * Function parse_character_range
 * 
 * A character range is defined to consist of a single letter or digit, followed by '-', which is followed by another letter or digit 
 * 
 * @param Parser A pointer to a Parser structure containing the source string and the current parsing state
 * 
 * @return A token containing all information needed to represent a character range
 */
struct Token *parse_character_range(struct Parser *parser) {
    char first, last;
    if(!parse_character_range_character(parser, &first)) {
        return NULL;
    }

    if(!parse_symbol(parser, '-')) {
        return NULL;
    }

    if(!parse_character_range_character(parser, &last)) {
        return NULL;
    }

    return create_character_range(first, last);
}

/**
 * function parse_character_class
 * 
 * A character class consists of single characters and character ranges
 * It may look like this [abcdefg], [a-gA-G], or [abc0-9def] 
 * 
 * @param Parser A pointer to a Parser structure containing the source string and the current parsing state
 * 
 * @returns A token that contains all information needed to represent a character class
 */
struct Token *parse_character_class(struct Parser *parser) {
    if(!parse_symbol(parser, '[')) {
        return NULL;
    }

    struct List *ranges = NULL;
    char *characters = calloc(1, sizeof(char));

    while(is_character_class_character(parser->current_character)) {
        if((parser_peek(parser, 1) == '-') && is_character_range_character(parser_peek(parser, 2))) {
            ranges = push(ranges, parse_character_range(parser));
        } else {
            characters = realloc(characters, (strlen(characters) + 2));
            strcat(characters, (char[]){parser->current_character, 0});
            parser_advance(parser);
        }
    }

    if(!parse_symbol(parser, ']')) {
        return NULL;
    }

    printf("%s\n", characters);
    return create_character_class(ranges, characters);
}

/**
 * Function parser_Free
 * 
 * @param parser Parser that we want to free
 */
void parser_free(struct Parser *parser) {
    free(parser->source);
    free(parser);
}