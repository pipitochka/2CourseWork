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
    codeGeneratorTest("1 TEST", "../../Tests/in/1.c", "../../Tests/out/1_out.s", 
                    "../../Tests/expected/1_expect.s");
    codeGeneratorTest("2 TEST", "../../Tests/in/2.c", "../../Tests/out/2_out.s", 
                    "../../Tests/expected/2_expect.s");
    codeGeneratorTest("3 TEST", "../../Tests/in/3.c", "../../Tests/out/3_out.s", 
                    "../../Tests/expected/3_expect.s");
    codeGeneratorTest("4 TEST", "../../Tests/in/4.c", "../../Tests/out/4_out.s", 
                    "../../Tests/expected/4_expect.s");
    codeGeneratorTest("5 TEST", "../../Tests/in/5.c", "../../Tests/out/5_out.s", 
                    "../../Tests/expected/5_expect.s");
    codeGeneratorTest("6 TEST", "../../Tests/in/6.c", "../../Tests/out/6_out.s", 
                    "../../Tests/expected/6_expect.s");
    codeGeneratorTest("7 TEST", "../../Tests/in/7.c", "../../Tests/out/7_out.s", 
                    "../../Tests/expected/7_expect.s");
    codeGeneratorTest("8 TEST", "../../Tests/in/8.c", "../../Tests/out/8_out.s", 
                    "../../Tests/expected/8_expect.s");
}