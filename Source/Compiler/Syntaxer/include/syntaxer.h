#ifndef SYNTAXER_H
#define SYNTAXER_H

#include "../../../All/Node/include/node.h"
#include "../../../All/Token/include/token.h"
#include "../../../Safe/Error/include/error.h"
#include "../../../All/Triple/include/triple.h"

Node* createAST(Token* token);

void printAST(const Node* node);

Triple* getTriple();

#endif //SYNTAXER_H
