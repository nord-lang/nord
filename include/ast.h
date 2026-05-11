#ifndef NORD_AST_H
#define NORD_AST_H

typedef enum {
    NODE_STREAM,
    NODE_ACTOR,
    NODE_CHANNEL,
    NODE_EXPR,
    NODE_ASSIGN
} NodeType;

typedef struct Node {
    NodeType type;
    struct Node* left;
    struct Node* right;
    char* value;
} Node;

typedef struct {
    Node** items;
    int count;
    int capacity;
} NodeList;

Node* node_create(NodeType type, const char* value);
void node_free(Node* node);

#endif