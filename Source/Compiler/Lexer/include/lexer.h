#ifndef LEXER_H
#define LEXER_H

#include "../../../All/Token/include/token.h"


enum States {NONE_STATE, WORD_STATE, NUMBER_STATE, STRING_STATE, CHAR_STATE, SCOPE_STATE,
    DELIMITER_STATE, OPERATOR_STATE, END_STATE, INCLUDE_STATE};

//function to make Token list from file
Token* lexer(char* name);

#endif //LEXER_H
