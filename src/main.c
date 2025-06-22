#include <stdio.h>

#include "lexer.h"
#include "token.h"

void print_token(Token tok) {
    const char *type_str;
    switch (tok.type) {
        case TOKEN_INTEGER:
            type_str = "INTEGER";
            break;
        case TOKEN_PLUS:
            type_str = "PLUS";
            break;
        case TOKEN_MINUS:
            type_str = "MINUS";
            break;
        case TOKEN_ASTERISK:
            type_str = "ASTERISK";
            break;
        case TOKEN_SLASH:
            type_str = "SLASH";
            break;
        case TOKEN_EOF:
            type_str = "EOF";
            break;
        default:
            type_str = "ILLEGAL";
            break;
    }
    printf("Token(Type: %s, Value: '%s')\n", type_str, tok.value ? tok.value : "null");
}

int main(int argc, char *argv[]) {
    const char *input = "10 + 25 - 5 * 39 / 21";
    Lexer *lexer = new_lexer(input);
    printf("Lexing input: \"%s\"\n", input);
    Token tok;

    do {
        tok = get_next_token(lexer);
        print_token(tok);
    } while (tok.type != TOKEN_EOF);
    return 0;
}
