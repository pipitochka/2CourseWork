#ifndef TOKEN_H
#define TOKEN_H

#include "vector.h"

enum TokenType {NONE, STRING, CHAR, SCOPE_OPEN, SCOPE_CLOSE, DELIMITER, OPERATOR, KWORD};

typedef struct Tok{
    enum TokenType type;
    Vector * vec;
    struct Tok* next;
    int order;
} Token;

Token* initToken();

void printTokens(const Token* token);

void freeTokens(Token* token);

void checkKeyword(const Token* token);

#endif //TOKEN_H
