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
    codeGeneratorTest("1 TEST", "../../Source/Compiler/CodeGenerator/tests/1.c", "../../Source/Compiler/CodeGenerator/tests/1_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/1_expect.s");
    codeGeneratorTest("2 TEST", "../../Source/Compiler/CodeGenerator/tests/2.c", "../../Source/Compiler/CodeGenerator/tests/2_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/2_expect.s");
    codeGeneratorTest("3 TEST", "../../Source/Compiler/CodeGenerator/tests/3.c", "../../Source/Compiler/CodeGenerator/tests/3_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/3_expect.s");
    codeGeneratorTest("4 TEST", "../../Source/Compiler/CodeGenerator/tests/4.c", "../../Source/Compiler/CodeGenerator/tests/4_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/4_expect.s");
    codeGeneratorTest("5 TEST", "../../Source/Compiler/CodeGenerator/tests/5.c", "../../Source/Compiler/CodeGenerator/tests/5_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/5_expect.s");
    codeGeneratorTest("6 TEST", "../../Source/Compiler/CodeGenerator/tests/6.c", "../../Source/Compiler/CodeGenerator/tests/6_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/6_expect.s");
    codeGeneratorTest("7 TEST", "../../Source/Compiler/CodeGenerator/tests/7.c", "../../Source/Compiler/CodeGenerator/tests/7_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/7_expect.s");
    codeGeneratorTest("8 TEST", "../../Source/Compiler/CodeGenerator/tests/8.c", "../../Source/Compiler/CodeGenerator/tests/8_out.s", 
                    "../../Source/Compiler/CodeGenerator/tests/8_expect.s");
}