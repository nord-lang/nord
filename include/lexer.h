#ifndef NORD_LEXER_H
#define NORD_LEXER_H

typedef enum {
    TOKEN_EOF,
    TOKEN_IDENT,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_ACTOR,
    TOKEN_STREAM,
    TOKEN_LET,
    TOKEN_MUT,
    TOKEN_FN,
    TOKEN_PUB,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_MATCH,
    TOKEN_RANGE,
    TOKEN_PIPE,
    TOKEN_FAT_ARROW,
    TOKEN_ARROW,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_ASSIGN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LTE,
    TOKEN_GTE,
} TokenType;

typedef struct {
    TokenType type;
    char* value;
    int line;
    int col;
} Token;

Token* lex(const char* source, int* count);
void tokens_free(Token* tokens, int count);

#endif