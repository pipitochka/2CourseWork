#ifndef TOKEN_H
#define TOKEN_H

#include "../../Vector/include/vector.h"

enum TokenType {NONE, STRING, CHAR, SCOPE_OPEN, SCOPE_CLOSE, DELIMITER, BIN_OPERATOR,
    UNAR_OPERATOR, KWORD, INCLUDE, NAME, NUMBER, SCOPE};

//enum TokenType {NONE, , , SCOPE_OPEN, SCOPE_CLOSE, , , , , };


typedef struct Token{
    enum TokenType type;
    Vector * vec;
    struct Token* next;
    int order;
} Token;

//function to allocate memory for token
Token* initToken();

//helper function to print tokens
void printTokens(const Token* token);

//function to deallocate memory for list of tokens
void deleteTokens(Token* token);

//function to deallocate memory for concretion token
void deleteToken(Token* token);

//function to check if word in  keyword
int checkKeyword(Token* token);

#endif //TOKEN_H
