#include "token.h"
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
        printf("%s", token->vec->data);
        printf("\n");
        token = token->next ? token->next : NULL;
    }
}

void freeTokens(Token* token) {
    if (token && token->next != NULL) {
        freeTokens(token->next);
    }
    if (token && token->vec != NULL) {
        freeVector(token->vec);
    }
    free(token);
}


