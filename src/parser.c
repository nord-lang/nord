#include "parser.h"
#include <stdlib.h>

Parser parser_create(Token* tokens, int count) {
    Parser p = {tokens, count, 0};
    return p;
}

static Token cur(Parser* p) { return p->tokens[p->pos]; }
static Token peek(Parser* p) { return p->pos + 1 < p->count ? p->tokens[p->pos + 1] : (Token){TOKEN_EOF, NULL, 0, 0}; }
static void advance(Parser* p) { p->pos++; }

static Node* parse_primary(Parser* p) {
    Token t = cur(p);
    if (t.type == TOKEN_NUMBER) {
        Node* n = node_create(NODE_EXPR, t.value);
        advance(p);
        return n;
    }
    return NULL;
}

Node* parse_expr(Parser* p) {
    return parse_primary(p);
}

Node* parse_program(Parser* p) {
    Node* prog = node_create(NODE_EXPR, "program");
    while (cur(p).type != TOKEN_EOF) {
        Node* stmt = parse_expr(p);
        if (!stmt) break;
        stmt->left = prog->right;
        prog->right = stmt;
    }
    return prog;
}