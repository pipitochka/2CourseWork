#ifndef TOKEN_H
#define TOKEN_H

#include "vector.h"

enum TokenType {NONE, STRING, CHAR, SCOPE_OPEN, SCOPE_CLOSE, DELIMITER};

typedef struct Tok{
    enum TokenType type;
    Vector * vec;
    struct Tok* next;
} Token;

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

void printToken(const Token* token) {
    while (token != NULL) {
        printf("%s", token->vec->data);
        printf("\n");
        token = token->next ? token->next : NULL;
    }
}

void freeToken(Token* token) {
    if (token && token->next != NULL) {
        freeToken(token->next);
    }
    if (token && token->vec != NULL) {
        freeVector(token->vec);
    }
    free(token);
}

#endif //TOKEN_H
