#include "Source/Compiler/Lexer/include/lexer.h"
#include "Source/Compiler/Syntaxer/include/syntaxer.h"
#include "Source/Compiler/CodeGenerator/include/codeGenerator.h"


int main() {
    Token* tokens = lexer("../text.in");
    Node* q = createAST(tokens);
    //printAST(q);
    
    generateCode(q, "../text.out", getTriple());
    
    
    freeNode(q);
    //printTokens(tokens);
    deleteTokens(tokens);
    
    return 0;
}
