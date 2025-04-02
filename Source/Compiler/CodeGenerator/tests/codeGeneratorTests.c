#include "../include/codeGenerator.h"
#include "../../../Compiler/Syntaxer/include/syntaxer.h"
#include "../../../Compiler/Lexer/include/lexer.h"
#include <stdlib.h>
#include <stdio.h>

void prepare(char* name, char* input, char* output) {
    Token* tokens = lexer(input);
    Node* q = createAST(tokens);
    
    generateCode(q, output, getTriple());
    
    deleteTokens(tokens);
    freeNode(q);
}


int codeGeneratorTest(char* name, char* input, char* output, char* expected) {
  
    FILE* fileExpect = fopen(expected, "r");
    FILE* fileReal = fopen(output, "r");
    
    while (!feof(fileReal) && !feof(fileExpect)) {
        char c = fgetc(fileReal);
        char c1 = fgetc(fileExpect);
        if (c != c1) {
            fclose(fileReal);
            fclose(fileExpect);
            printf("Not equvalet");
            return 0;
        }
    }
    fclose(fileReal);
    fclose(fileExpect);
    printf("Test success");
    return 1;
   
}


int main() {    
    codeGeneratorTest("1 TEST", "../../Source/Compiler/CodeGenerator/tests/1.in", "../../Source/Compiler/CodeGenerator/tests/1.out", 
                    "../../Source/Compiler/CodeGenerator/tests/1.expect");
}