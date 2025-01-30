#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../All/Token/include/token.h"

enum States {NONE_STATE, WORD_STATE, NUMBER_STATE, STRING_STATE, CHAR_STATE, SCOPE_STATE,
    DELIMITER_STATE, OPERATOR_STATE, END_STATE, INCLUDE_STATE};

Token* lexer(char* name);

#endif //LEXER_H
