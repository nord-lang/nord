#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.no>\n", argv[0]);
        return 1;
    }
    
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        return 1;
    }
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* source = malloc(size + 1);
    fread(source, 1, size, f);
    source[size] = '\0';
    fclose(f);
    
    int count;
    Token* tokens = lex(source, &count);
    
    printf("Tokens:\n");
    for (int i = 0; i < count; i++) {
        printf("  %d: %s", tokens[i].type, tokens[i].value ? tokens[i].value : "(null)");
        printf(" (%d:%d)\n", tokens[i].line, tokens[i].col);
    }
    
    tokens_free(tokens, count);
    free(source);
    return 0;
}