#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int test_lexer_numbers() {
    const char* src = "123 456 789";
    int count;
    Token* tokens = lex(src, &count);
    
    if (tokens[0].type != TOKEN_NUMBER) return 1;
    if (strcmp(tokens[0].value, "123") != 0) return 2;
    if (tokens[1].type != TOKEN_NUMBER) return 3;
    if (strcmp(tokens[1].value, "456") != 0) return 4;
    
    tokens_free(tokens, count);
    printf("  ✓ lexer numbers test passed\n");
    return 0;
}

int test_lexer_keywords() {
    const char* src = "actor stream let mut fn";
    int count;
    Token* tokens = lex(src, &count);
    
    if (tokens[0].type != TOKEN_ACTOR) return 1;
    if (tokens[1].type != TOKEN_STREAM) return 2;
    if (tokens[2].type != TOKEN_LET) return 3;
    if (tokens[3].type != TOKEN_MUT) return 4;
    if (tokens[4].type != TOKEN_FN) return 5;
    
    tokens_free(tokens, count);
    printf("  ✓ lexer keywords test passed\n");
    return 0;
}

int test_lexer_operators() {
    const char* src = "=> -> == |> =";
    int count;
    Token* tokens = lex(src, &count);
    
    if (tokens[0].type != TOKEN_FAT_ARROW) return 1;
    if (tokens[1].type != TOKEN_ARROW) return 2;
    if (tokens[2].type != TOKEN_EQ) return 3;
    if (tokens[3].type != TOKEN_PIPE) return 4;
    if (tokens[4].type != TOKEN_ASSIGN) return 5;
    
    tokens_free(tokens, count);
    printf("  ✓ lexer operators test passed\n");
    return 0;
}

int main() {
    printf("Running Nord tests...\n");
    
    int failed = 0;
    failed += test_lexer_numbers();
    failed += test_lexer_keywords();
    failed += test_lexer_operators();
    
    if (failed == 0) {
        printf("All tests passed!\n");
        return 0;
    } else {
        printf("%d tests failed!\n", failed);
        return 1;
    }
}