#include <stdlib.h>
#include <string.h>

#include "../includes/token.h"
#include "../includes/util.h"

struct Token *create_character_class(struct List *ranges, char *characters) {
    struct Token *token = safe_malloc(sizeof(struct Token));
    struct CharacterClass *character_class = safe_malloc(sizeof(struct CharacterClass));

    character_class->character_ranges = ranges;
    character_class->characters = strdup(characters);

    token->type = CHARACTER_CLASS;
    token->character_class_data = character_class;
    token->next = NULL;

    return token;
}

struct Token *create_character_range(char first, char last) {
    struct Token *token = safe_malloc(sizeof(struct Token));
    struct CharacterRange *range = safe_malloc(sizeof(struct CharacterRange));

    range->first = first;
    range->last = last;

    token->type = CHARACTER_RANGE;
    token->character_range_data = range;
    token->next = NULL;

    return token;
}