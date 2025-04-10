#ifndef SYNTAXER_H
#define SYNTAXER_H

#include "../../../All/Node/include/node.h"
#include "../../../All/FunctionList/include/functionList.h"

Node* createAST(Token* token);

void printAST(const Node* node);

#endif //SYNTAXER_H
