#ifndef SYNTAXER_H
#define SYNTAXER_H

#include "../../../All/Node/include/node.h"

Node* createAST(Token* token);

void printAST(const Node* node);

Variable* getTriple();

#endif //SYNTAXER_H
