#include "Source/Compiler/Lexer/include/lexer.h"
#include "Source/Compiler/Syntaxer/include/syntaxer.h"
#include "Source/All/Node/include/node.h"
#include "Source/Compiler/CodeGenerator/include/codeGenerator.h"


int main() {
    Token* tokens = lexer("../text.in");
    Node* q = createAST(tokens);
    printAST(q);
    
    Vector* code = generateCode(q);
    freeVector(code);
    
    
    //freeNode(q);
    printTokens(tokens);
    deleteTokens(tokens);
    
    return 0;
}
