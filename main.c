#include <stdio.h>

#include "parser.h"
#include "token.h"
#include "list.h"

int main() {
    struct Parser *parser = create_parser("[a-zAB0-9CDEFG-_]");
    struct Token *token = parse_character_class(parser);

    parser_free(parser);
}