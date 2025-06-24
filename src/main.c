#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "lexer.h"
#include "parser.h"
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

void print_ast(ASTNode *node) {
    if (node == nullptr) {
        printf("null node");
        return;
    }

    if (node->type == AST_INFIX_EXPRESSION) {
        InfixExpression *infix = (InfixExpression *)node;
        printf("(");
        print_ast(infix->left);
        printf(" %s ", infix->token.value);
        print_ast(infix->right);
        printf(" %s ", infix->token.value);
        printf(")");
    } else if (node->type == AST_INTEGER_LITERAL) {
        IntegerLiteral *integer = (IntegerLiteral *)node;
        printf("%ld", integer->value);
    } else {
        printf("Unknown node");
    }
}

int main() {
    const char *input = "10 + 25 - 5 * 39 / 21";
    Lexer *lexer = new_lexer(input);
    Parser *parser = new_parser(lexer);
    printf("Parsing input: \"%s\"\n", input);
    ASTNode *expression = parse_expression(parser);

    if (expression) {
        printf("Generated AST");
        print_ast(expression);
        printf("\n");
    } else {
        printf("Failed to parse expression. \n");
    }
    free(lexer);
    free(parser);
    return 0;
}
