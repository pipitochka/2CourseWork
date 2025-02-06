#include "Source/Compiler/Lexer/include/lexer.h"
#include "Source/Compiler/Syntaxer/include/syntaxer.h"
#include "Source/All/Node/include/node.h"

int main() {
    Token* tokens = lexer("../test.txt");
    Node* q = createAST(tokens);
    printAST(q);
    //printTokens(tokens);
    deleteTokens(tokens);
    
    return 0;
}
