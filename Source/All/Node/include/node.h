#ifndef NODE_H
#define NODE_H
#include <stdbool.h>
#include <stdlib.h>

#include "../../Token/include/token.h"

enum NodeType {NULL_NODE, DATA_NODE};

typedef struct Node{
    Token* token;
    enum NodeType type;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    struct Node* next;
    struct Node* prev;
    struct Node* bottom;
    struct Node* top;
    int generated;
} Node;

Node* createNode();

void freeNode(Node* node);

// int addChild(Node* parent, Node* children);
//
// void deleteNode(Node* node);
//
// void changeChild(Node* parent, Node* from, Node* to);

#endif //NODE_H
