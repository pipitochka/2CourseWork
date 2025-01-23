#include "../lexer.h"
#include "../SafeAssert/safeAssert.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>


int compareVectors(const Vector *a, const Vector *b, Token *token) {
    int t = 0;
    if (safeAssert((a == NULL || b == NULL) || (a->size == b->size), token) == 0) {
        return 0;
    }
    while (t < a->size && t < b->size) {
        if (safeAssert(a->data[t] == b->data[t], token) == 0) {
            return 0;
        }
        t++;
    };
    return 1;
}

int lexerTest(char* name, char* input, char* expected) {
    Token* token = lexer(input);
    Token* first = token;
    safeAssert(token != NULL, token);
    if (token == NULL) {
        return 0;
    }
    token = token->next;
    //printTokens(token);
    FILE* file = fopen(expected, "r");

    char c = fgetc(file);
    while(c != EOF) {
        Vector* result = initVector();


        while (c != '\n' && c != EOF) {
            pushBackVector(result, c);
            c = fgetc(file);
        }
        //printf("%s\n", token->vec->data);
        //printf("%s\n", result->data);
        if (compareVectors(token->vec, result, first) == 0) {
            return 0;
        }
        freeVector(result);

        token = token->next;
        c = fgetc(file);
    }
    printf("%s tests passed\n", name);
    return 1;
}


int main() {
    // lexerTest("1 test", "../Lexer/tests/1_input.txt", "../Lexer/tests/1_output.txt");
    // lexerTest("2 test", "../Lexer/tests/2_input.txt", "../Lexer/tests/2_output.txt");
    // lexerTest("3 test", "../Lexer/tests/3_input.txt", "../Lexer/tests/3_output.txt");
    // lexerTest("4 test", "../Lexer/tests/4_input.txt", "../Lexer/tests/4_output.txt");
    // lexerTest("5 test", "../Lexer/tests/5_input.txt", "../Lexer/tests/5_output.txt");

    lexerTest("1 test", "../../Source/Lexer/tests/1_input.txt", "../../Source/Lexer/tests/1_output.txt");
    lexerTest("2 test", "../../Source/Lexer/tests/2_input.txt", "../../Source/Lexer/tests/2_output.txt");
    lexerTest("3 test", "../../Source/Lexer/tests/3_input.txt", "../../Source/Lexer/tests/3_output.txt");
    lexerTest("4 test", "../../Source/Lexer/tests/4_input.txt", "../../Source/Lexer/tests/4_output.txt");
    lexerTest("5 test", "../../Source/Lexer/tests/5_input.txt", "../../Source/Lexer/tests/5_output.txt");
}