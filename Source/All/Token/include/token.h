#ifndef TOKEN_H
#define TOKEN_H

#include "../../Vector/include/vector.h"

enum TokenType {NONE, STRING, CHAR, SCOPE_OPEN, SCOPE_CLOSE, DELIMITER, OPERATOR, KWORD, INCLUDE, NAME};

typedef struct Tok{
    enum TokenType type;
    Vector * vec;
    struct Tok* next;
    int order;
} Token;

Token* initToken();

void printTokens(const Token* token);

void freeTokens(Token* token);

int checkKeyword(Token* token);

#endif //TOKEN_H
