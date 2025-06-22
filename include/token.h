#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_ILLEGAL,  // these are illegal token we do not support.
    TOKEN_EOF,      // recognise the end of the file.
    TOKEN_INTEGER,  // all the integers.
    TOKEN_PLUS,     // '+'
    TOKEN_MINUS,    // '-'
    TOKEN_ASTERISK, // '*'
    TOKEN_SLASH,    // '/'
} TokenType;

typedef struct Token {
    TokenType type;
    char *value; // this is actual string from the source
} Token;

#endif
