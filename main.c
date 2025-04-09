#include "Source/Compiler/Lexer/include/lexer.h"
#include "Source/Compiler/Syntaxer/include/syntaxer.h"
#include "Source/Compiler/CodeGenerator/include/codeGenerator.h"
#include "Source/Safe/Error/include/error.h"


int main() {
    Token* tokens = lexer("../text.in");
    Node* q = createAST(tokens);
    //printAST(q);
    
    generateCode(q, "../text.out");
    
    
    freeNode(q);
    //printTokens(tokens);
    deleteTokens(tokens);
    
    return 0;
}

//
// int main(char argc, char** argv) {
//     
// }