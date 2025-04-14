#ifndef NODE_H
#define NODE_H


#include "../../Token/include/token.h"
#include "../../Function/include/function.h"

enum NodeType {NULL_NODE, DATA_NODE, FUNCTION, FUNCTION_CALL, RETURN_NODE};

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
    Function* function;
    int generated;
} Node;

//function to allocate memory for Node
Node* createNode();

//function to deallocate memory allocated for Node tree
void freeNode(Node* node);

#endif //NODE_H
