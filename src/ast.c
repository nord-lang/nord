#define _POSIX_C_SOURCE 200809L
#include "ast.h"
#include <stdlib.h>
#include <string.h>

Node* node_create(NodeType type, const char* value) {
    Node* node = malloc(sizeof(Node));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->value = value ? strdup(value) : NULL;
    return node;
}

void node_free(Node* node) {
    if (!node) return;
    node_free(node->left);
    node_free(node->right);
    free(node->value);
    free(node);
}