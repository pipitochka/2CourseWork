#ifndef NODE_H
#define NODE_H
#include "../../Token/include/token.h"

typedef struct Node{
  Token* token;
  struct Node* parent;
  int numChildren;
  struct Node** children;
} Node;

Node* createNode();

int addChild(Node* parent, Node* children);

#endif //NODE_H
