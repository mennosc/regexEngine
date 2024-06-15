#include <stdio.h>

#include "../includes/parser.h"
#include "../includes/token.h"
#include "../includes/list.h"

int main() {
    struct Parser *parser = create_parser("[a-zAB0-9CDEFG-_]");
    struct Token *token = parse_character_class(parser);

    parser_free(parser);
}