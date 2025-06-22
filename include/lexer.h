#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct Lexer {
    const char *input; // the string we will scan
    int position;      // current position in input ( points to current char )
    int readPosition;  // current reading position ( after current char )
    char ch;           // current charector under examination
} Lexer;

Lexer *new_lexer(const char *input);

Token get_next_token(Lexer *lexer);

#endif
