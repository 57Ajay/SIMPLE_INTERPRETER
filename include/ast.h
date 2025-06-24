#ifndef AST_H
#define AST_H

#include "token.h"

// This enum is for identifying the AST node
typedef enum ASTNodeType {
    AST_INTEGER_LITERAL,
    AST_INFIX_EXPRESSION,
} ASTNodeType;

// the base node for all of AST
// so, besically the idea is that the type will tell us which specific type of node
// we are working on.
typedef struct ASTNode {
    ASTNodeType type;
} ASTNode;

typedef struct IntegerLiteral {
    ASTNode node;
    Token token;
    long value;
} IntegerLiteral;

typedef struct InfixExpression {
    ASTNode node;
    Token token;
    ASTNode *left;
    ASTNode *right;
} InfixExpression;

#endif
