#include "Source/Compiler/Lexer/include/lexer.h"
#include "Source/Compiler/Syntaxer/include/syntaxer.h"
#include "Source/Compiler/CodeGenerator/include/codeGenerator.h"
#include "Source/Safe/Error/include/error.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc > 3 || argc == 1) {
        printf("Error: expected another amount of arguments");
        return 1;
    }
    char* output_path = "out.s";
    char* input_path = argv[1];
    if (argc == 3) {
        output_path = argv[2];
    }
    
    Token* tokens = lexer(input_path);
    Node* q = createAST(tokens);
    generateCode(q, output_path);
    freeNode(q);
    deleteTokens(tokens);
    
    return 0;
}
