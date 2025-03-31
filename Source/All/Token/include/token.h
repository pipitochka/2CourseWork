#ifndef TOKEN_H
#define TOKEN_H

#include "../../Vector/include/vector.h"

enum TokenType {NONE, STRING, CHAR, SCOPE_OPEN, SCOPE_CLOSE, DELIMITER, BIN_OPERATOR,
    UNAR_OPERATOR, KWORD, INCLUDE, NAME, NUMBER, SCOPE};

//enum TokenType {NONE, , , SCOPE_OPEN, SCOPE_CLOSE, , , , , };


typedef struct Tok{
    enum TokenType type;
    Vector * vec;
    struct Tok* next;
    int order;
} Token;

Token* initToken();

void printTokens(const Token* token);

void deleteTokens(Token* token);

void deleteToken(Token* token);

int checkKeyword(Token* token);

#endif //TOKEN_H
