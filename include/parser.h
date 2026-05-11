#ifndef NORD_PARSER_H
#define NORD_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Token* tokens;
    int count;
    int pos;
} Parser;

Parser parser_create(Token* tokens, int count);
Node* parse_expr(Parser* p);
Node* parse_program(Parser* p);

#endif