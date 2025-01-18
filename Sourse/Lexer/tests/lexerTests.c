#include "../lexer.c"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>


void compareVectors(Vector *a, Vector *b) {
    int t = 0;
    while (t < a->size && t < b->size) {
        assert(a->data[t] == b->data[t]);
        t++;
    };
}

void lexerTest(char* name, char* input, char* expected) {
    Token* token = lexer(input);
    Token* first = token;
    token = token->next;

    FILE* file = fopen(expected, "r");

    char c = fgetc(file);
    while(c != EOF) {
        Vector* result = initVector();


        while (c != '\n' && c != EOF) {
            pushBackVector(result, c);
            c = fgetc(file);
        }
        compareVectors(token->vec, result);

        freeVector(result);

        token = token->next;
        c = fgetc(file);
    }
    printf("%s tests passed\n", name);
}


int main() {
    lexerTest("1 test", "../Lexer/tests/1_input.txt", "../Lexer/tests/1_output.txt");
    lexerTest("2 test", "../Lexer/tests/2_input.txt", "../Lexer/tests/2_output.txt");
    lexerTest("3 test", "../Lexer/tests/3_input.txt", "../Lexer/tests/3_output.txt");
    lexerTest("4 test", "../Lexer/tests/4_input.txt", "../Lexer/tests/4_output.txt");
    lexerTest("5 test", "../Lexer/tests/5_input.txt", "../Lexer/tests/5_output.txt");

}