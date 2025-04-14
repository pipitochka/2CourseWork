#include "../include/token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../../Safe/Error/include/error.h"

//allocate memory for token
//if allocation can not be done return NULL and print error message
//makes all fields 0 or NULL
//return point on allocation token
Token* initToken() {
    Token* new = (Token*)malloc(sizeof(Token));
    if (new == NULL) {
        printErrorMessage(5);
        return NULL;
    }
    new->vec = initVector();
    new->next = NULL;
    new->type = NONE;
    return new;
}

//function to print tokens
//recursively print tokens
void printTokens(const Token* token) {
    while (token != NULL) {
        if (token->vec != NULL) {
            printf("%s", token->vec->data);
            printf("\n");
        }
        token = token->next ? token->next : NULL;
    }
}

//function to delete tokens
//recursively delete tokens with vector inside
void deleteTokens(Token* token) {
    if (token && token->next != NULL) {
        deleteTokens(token->next);
    }
    if (token) {
        freeVector(token->vec);
    }
    free(token);
}

//function to delete token
//delete vector too
void deleteToken(Token* token) {
    free(token->vec);
    free(token);
}

//list of keyword which can not be used as variables
char* keywords[] = {
    "for",
    "while",
    "int",
    "char",
    "true",
    "false",
    "if",
    "else",
    "void",
    "return"
};

//function to compare token with keywords
//if token is keyword change token type
int checkKeyword(Token* token) {
    if (token == NULL || token->vec == NULL || token->vec->data == NULL) {
        return -1;
    }

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token->vec->data, keywords[i]) == 0) {
            token->type = KWORD;
            return 1;
        }
    }

    token->type = NAME;
    return 0;
}



