#ifndef SYNTAXER_H
#define SYNTAXER_H

#include "../../../All/Node/include/node.h"
#include "../../../All/FunctionList/include/functionList.h"

//function to make AST from token list
Node* createAST(Token* token);

//addition function for debug
void printAST(const Node* node);

#endif //SYNTAXER_H
