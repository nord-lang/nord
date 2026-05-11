#define _POSIX_C_SOURCE 200809L
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char* keywords[] = {
    "actor", "stream", "let", "mut", "fn", "pub", "if", "else", "match", "range"
};
static const TokenType keyword_tokens[] = {
    TOKEN_ACTOR, TOKEN_STREAM, TOKEN_LET, TOKEN_MUT, TOKEN_FN, TOKEN_PUB,
    TOKEN_IF, TOKEN_ELSE, TOKEN_MATCH, TOKEN_RANGE
};
#define KEYWORD_COUNT 10

static Token* tokens_add(Token* tokens, int* count, int* capacity, Token t) {
    if (*count >= *capacity) {
        *capacity = *capacity ? *capacity * 2 : 64;
        tokens = realloc(tokens, *capacity * sizeof(Token));
    }
    tokens[(*count)++] = t;
    return tokens;
}

static TokenType ident_to_keyword(const char* s) {
    for (int i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(s, keywords[i]) == 0) return keyword_tokens[i];
    }
    return TOKEN_IDENT;
}

Token* lex(const char* source, int* count) {
    Token* tokens = NULL;
    int capacity = 0;
    *count = 0;
    
    int line = 1, col = 1;
    while (*source) {
        if (isspace(*source)) {
            if (*source == '\n') { line++; col = 1; }
            else { col++; }
            source++;
            continue;
        }
        
        Token t = {0};
        t.line = line; t.col = col;
        
        if (isalpha(*source) || *source == '_') {
            const char* start = source;
            while (isalnum(*source) || *source == '_') source++, col++;
            int len = source - start;
            char* ident = strndup(start, len);
            t.type = ident_to_keyword(ident);
            t.value = (t.type == TOKEN_IDENT) ? ident : NULL;
            tokens = tokens_add(tokens, count, &capacity, t);
            if (t.type != TOKEN_IDENT) free(ident);
            continue;
        }
        
        if (isdigit(*source) || (*source == '.' && isdigit(*(source+1)))) {
            const char* start = source;
            while (isdigit(*source) || *source == '.') source++, col++;
            t.type = TOKEN_NUMBER;
            t.value = strndup(start, source - start);
            tokens = tokens_add(tokens, count, &capacity, t);
            continue;
        }
        
        switch (*source) {
            case '|': t.type = TOKEN_PIPE; t.value = strdup("|>"); source++; col++; break;
            case '=': 
                if (*(source+1) == '>') { t.type = TOKEN_FAT_ARROW; t.value = strdup("=>"); source += 2; col += 2; }
                else if (*(source+1) == '=') { t.type = TOKEN_EQ; t.value = strdup("=="); source += 2; col += 2; }
                else { t.type = TOKEN_ASSIGN; t.value = strdup("="); source++; col++; }
                break;
            case '-': 
                if (*(source+1) == '>') { t.type = TOKEN_ARROW; t.value = strdup("->"); source += 2; col += 2; }
                else { t.type = TOKEN_MINUS; t.value = strdup("-"); source++; col++; }
                break;
            case '+': t.type = TOKEN_PLUS; t.value = strdup("+"); source++; col++; break;
            case '*': t.type = TOKEN_STAR; t.value = strdup("*"); source++; col++; break;
            case '/': t.type = TOKEN_SLASH; t.value = strdup("/"); source++; col++; break;
            case '%': t.type = TOKEN_PERCENT; t.value = strdup("%"); source++; col++; break;
            case '{': t.type = TOKEN_LBRACE; t.value = strdup("{"); source++; col++; break;
            case '}': t.type = TOKEN_RBRACE; t.value = strdup("}"); source++; col++; break;
            case '(': t.type = TOKEN_LPAREN; t.value = strdup("("); source++; col++; break;
            case ')': t.type = TOKEN_RPAREN; t.value = strdup(")"); source++; col++; break;
            case '[': t.type = TOKEN_LBRACKET; t.value = strdup("["); source++; col++; break;
            case ']': t.type = TOKEN_RBRACKET; t.value = strdup("]"); source++; col++; break;
            case ':': t.type = TOKEN_COLON; t.value = strdup(":"); source++; col++; break;
            case ';': t.type = TOKEN_SEMICOLON; t.value = strdup(";"); source++; col++; break;
            case ',': t.type = TOKEN_COMMA; t.value = strdup(","); source++; col++; break;
            case '<': t.type = (*(source+1)=='=') ? (source+=2,col+=2,TOKEN_LTE) : (source++,col++,TOKEN_LT); break;
            case '>': t.type = (*(source+1)=='=') ? (source+=2,col+=2,TOKEN_GTE) : (source++,col++,TOKEN_GT); break;
            default: source++; col++; continue;
        }
        tokens = tokens_add(tokens, count, &capacity, t);
    }
    
    Token eof = {TOKEN_EOF, NULL, line, col};
    tokens = tokens_add(tokens, count, &capacity, eof);
    return tokens;
}

void tokens_free(Token* tokens, int count) {
    for (int i = 0; i < count; i++) free(tokens[i].value);
    free(tokens);
}