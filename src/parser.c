#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lexer.h"
#include "token.h"

Parser *new_parser(Lexer *lexer) {
    Parser *parse = (Parser *)malloc(sizeof(Parser));
    if (!parse) {
        perror("Failed to allocate memory to parser");
        return nullptr;
    }

    parse->lexer = lexer;
    parse->currentToken = get_next_token(lexer);
    parse->peekToken = get_next_token(lexer);
    return parse;
}

ASTNode *parse_expression(Parser *parser) {
    if (parser->currentToken.type == TOKEN_INTEGER) {
        IntegerLiteral *int_node = (IntegerLiteral *)malloc(sizeof(IntegerLiteral));
        if (!int_node) {
            perror("Failed to allocate memory to IntegerLiteral node");
            return nullptr;
        }
        int_node->token = get_next_token(parser->lexer);
        int_node->node = (ASTNode){.type = AST_INTEGER_LITERAL};
        char *val;
        int_node->value = strtol(int_node->token.value, &val, 10);
        return &int_node->node;
    } else {
        return nullptr;
    }
}

void next_token(Parser *parser) {
    Token next_tok = get_next_token(parser->lexer);
    parser->currentToken = parser->peekToken;
    parser->peekToken = next_tok;
}
