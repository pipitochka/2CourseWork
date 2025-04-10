#include "../include/codeGenerator.h"
#include "../../../Compiler/Syntaxer/include/syntaxer.h"
#include "../../../Compiler/Lexer/include/lexer.h"
#include <stdlib.h>
#include <stdio.h>

void prepare(char* name, char* input, char* output) {
    Token* tokens = lexer(input);
    Node* q = createAST(tokens);
    
    //generateCode(q, output, getTriple());
    generateCode(q, output);

    
    deleteTokens(tokens);
    freeNode(q);
}


int codeGeneratorTest(char* name, char* input, char* output, char* expected) {

    Token* tokens = lexer(input);
    Node* q = createAST(tokens);
    generateCode(q, output);
    freeNode(q);
    deleteTokens(tokens);
    
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
    printf("Test %s success\n", name);
    return 1;
   
}


int main() {    
    codeGeneratorTest("1 TEST", "../../Source/Compiler/CodeGenerator/tests/1.in", "../../Source/Compiler/CodeGenerator/tests/1.out", 
                    "../../Source/Compiler/CodeGenerator/tests/1.expect");
    codeGeneratorTest("2 TEST", "../../Source/Compiler/CodeGenerator/tests/2.in", "../../Source/Compiler/CodeGenerator/tests/2.out", 
                    "../../Source/Compiler/CodeGenerator/tests/2.expect");
    codeGeneratorTest("3 TEST", "../../Source/Compiler/CodeGenerator/tests/3.in", "../../Source/Compiler/CodeGenerator/tests/3.out", 
                    "../../Source/Compiler/CodeGenerator/tests/3.expect");
    codeGeneratorTest("4 TEST", "../../Source/Compiler/CodeGenerator/tests/4.in", "../../Source/Compiler/CodeGenerator/tests/4.out", 
                    "../../Source/Compiler/CodeGenerator/tests/4.expect");
    codeGeneratorTest("5 TEST", "../../Source/Compiler/CodeGenerator/tests/5.in", "../../Source/Compiler/CodeGenerator/tests/5.out", 
                    "../../Source/Compiler/CodeGenerator/tests/5.expect");
    codeGeneratorTest("6 TEST", "../../Source/Compiler/CodeGenerator/tests/6.in", "../../Source/Compiler/CodeGenerator/tests/6.out", 
                    "../../Source/Compiler/CodeGenerator/tests/6.expect");
    codeGeneratorTest("7 TEST", "../../Source/Compiler/CodeGenerator/tests/7.in", "../../Source/Compiler/CodeGenerator/tests/7.out", 
                    "../../Source/Compiler/CodeGenerator/tests/7.expect");
    codeGeneratorTest("8 TEST", "../../Source/Compiler/CodeGenerator/tests/8.in", "../../Source/Compiler/CodeGenerator/tests/8.out", 
                    "../../Source/Compiler/CodeGenerator/tests/8.expect");
}