#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"

typedef struct Parser {
    Lexer *lexer;
    Token currentToken;
    Token peekToken;
} Parser;

Parser *new_parser(Lexer *lexer);

ASTNode *parse_expression(Parser *parser);

void next_token(Parser *parser);

#endif
