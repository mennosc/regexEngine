#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdbool.h>

struct Parser {
    char *source;
    char current_character;
    size_t source_length;
    size_t current_index;
};

//Function declarations
struct Parser *create_parser(char *source);
bool parse_number(struct Parser *parser, int *value);
bool parse_symbol(struct Parser *parser, char symbol);
bool parse_character_range_character(struct Parser *parser, char *value);
char parser_peek(struct Parser *parser, size_t offset);
struct Token *parse_character_range(struct Parser *parser);
struct Token *parse_range_quantifier(struct Parser *parser);
struct Token *parse_character_class(struct Parser *parser);
void parser_free(struct Parser *parser);

#endif