#include "../include/token.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Token* initToken() {
    Token* new = (Token*)malloc(sizeof(Token));
    if (new == NULL) {
        printf("Token allocation failed\n");
        exit(-1);
    }
    new->vec = initVector();
    new->next = NULL;
    new->type = NONE;
    return new;
}

void printTokens(const Token* token) {
    while (token != NULL) {
        if (token->vec != NULL) {
            printf("%s", token->vec->data);
            printf("\n");
        }
        token = token->next ? token->next : NULL;
    }
}

void deleteTokens(Token* token) {
    if (token && token->next != NULL) {
        deleteTokens(token->next);
    }
    if (token) {
        freeVector(token->vec);
    }
    free(token);
}

void deleteToken(Token* token) {
    free(token->vec);
    free(token);
}

char* keywords[] = {
    "for",
    "while",
    "int",
    "char",
    "main",
    "true",
    "false",
    "if",
    "else",
    "void",
    "return"
};

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



