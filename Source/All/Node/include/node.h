#ifndef NODE_H
#define NODE_H
#include <stdlib.h>

#include "../../Token/include/token.h"


typedef struct Node{
    Token* token;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode();

// int addChild(Node* parent, Node* children);
//
// void deleteNode(Node* node);
//
// void changeChild(Node* parent, Node* from, Node* to);

#endif //NODE_H
