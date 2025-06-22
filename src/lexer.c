#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void read_char(Lexer *lexer);
static void skip_whitespace(Lexer *lexer);
static char *read_number(Lexer *lexer);
static int is_digit(char chr);

Lexer *new_lexer(const char *input) {
    Lexer *lex = (Lexer *)malloc(sizeof(Lexer));
    if (!lex) {
        perror("Failed to allocate memory for lexer");
        return nullptr;
    }
    lex->input = input;
    lex->position = 0;
    lex->readPosition = 1;
    lex->ch = 0;

    // "Prime" the lexer by reading the first character.
    read_char(lex);

    return lex;
}

// the core job of read_char: advance the position in the input.
static void read_char(Lexer *lexer) {
    // Check if we've reached the end of the input string
    if (lexer->readPosition >= (int)strlen(lexer->input)) {
        lexer->ch = '\0'; //'\0' signify "end of file" or end of input
    } else {
        // Read the next character
        lexer->ch = lexer->input[lexer->readPosition];
    }
    // Advance our pointers
    lexer->position = lexer->readPosition;
    lexer->readPosition++;
}

static int is_digit(char chr) {
    return '0' <= chr && chr <= '9';
}

static char *read_number(Lexer *lexer) {
    int start_pos = lexer->position;
    while (is_digit(lexer->ch)) {
        read_char(lexer);
    }
    int length = lexer->position - start_pos;

    char *number_str = (char *)malloc(length + 1);
    if (!number_str) {
        perror("Failed to allocate memory for number string");
        return nullptr;
    }

    strncpy(number_str, lexer->input + start_pos, length);
    number_str[length] = '\0'; // ensuring that we Null-terminate the string

    return number_str;
}

static void skip_whitespace(Lexer *lexer) {
    while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r') {
        read_char(lexer);
    }
}

// function that analyzes the current character and returns the next token.
Token get_next_token(Lexer *lexer) {
    Token tok;

    skip_whitespace(lexer); // skip the whitespace first

    switch (lexer->ch) {
        case '+':
            tok = (Token){TOKEN_PLUS, "+"};
            break;
        case '-':
            tok = (Token){TOKEN_MINUS, "-"};
            break;
        case '*':
            tok = (Token){TOKEN_ASTERISK, "*"};
            break;
        case '/':
            tok = (Token){TOKEN_SLASH, "/"};
            break;
        case '\0':
            tok = (Token){TOKEN_EOF, ""};
            break;
        default:
            if (is_digit(lexer->ch)) {
                // If it's a digit, we start parsing a number.
                tok.type = TOKEN_INTEGER;
                tok.value = read_number(lexer);
                // read_number advances the lexer for us, so we just return.
                return tok;
            } else {
                // If we don't recognize the character, it's illegal.
                tok = (Token){TOKEN_ILLEGAL, ""};
            }
            break;
    }

    // ok, here advance the lexer so we're ready for the next call
    read_char(lexer);

    return tok;
}
