#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/lexer.h"
#include "../../../All//Token/include/tokenError.h"
#include "../../../Safe/Error/include/error.h"

Token* lexer(char* name) {
    FILE* file;

    Token* token = initToken(); ;
    Token* first = token;
    token->next = NULL;
    file = fopen(name, "r");
    if (file == NULL) {
        printErrorMessage(6);
        return NULL;
    }

    enum States state = NONE_STATE;

    char c = fgetc(file);
    while (!feof(file)) {
        switch (state) {
            case (NONE_STATE):
                while (c == ' ' || c == '\t' || c == '\n') {
                    c = getc(file);
                }
                if (c >= '0' && c <= '9') {
                    state = NUMBER_STATE;
                    break;
                }
                if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                    state = WORD_STATE;
                    break;
                }
                if (c == '\"') {
                    state = STRING_STATE;
                    break;
                }
                if (c == '\'') {
                    state = CHAR_STATE;
                    break;
                }
                if (c == '}' || c == '{') {
                    state = SCOPE_STATE;
                    break;
                }
                if (c == ')' || c == '(' || c == ',' || c == ';' || c == ']' || c == '[' || c == ':') {
                    state = DELIMITER_STATE;
                    break;
                }
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>'
                    || c == '&' || c == '|' || c == '!' || c == '~' || c == '^') {
                    state = OPERATOR_STATE;
                    break;
                }
                if (c == '#') {
                    state = INCLUDE_STATE;
                    break;
                }
                if (c == EOF) {
                    state = END_STATE;
                    break;
                }
                tokenError(token, 2);
                return NULL;
            case (NUMBER_STATE):
                if (c >= '0' && c <= '9') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    token->type = NUMBER;
                    while (!feof(file) && c >= '0' && c <= '9') {
                        pushBackVector(token->vec, c);
                        c = getc(file);
                    }
                    state = NONE_STATE;
                    if (!feof(file)) {
                        break;
                    }
                    else {
                        state = END_STATE;
                    }
                }
            case (WORD_STATE):
                if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    while (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                        pushBackVector(token->vec, c);
                        c = getc(file);
                    }
                    state = NONE_STATE;
                    if (!feof(file)) {
                        break;
                    }
                    else {
                        state = END_STATE;
                    }
                }
            case (STRING_STATE):
                if (c == '\"') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    token->type = STRING;
                    c = fgetc(file);
                    while (c != '\"' && !feof(file)) {
                        pushBackVector(token->vec, c);
                        c = getc(file);
                    }
                    if (c != '\"') {
                        tokenError(first, 1);
                        return NULL;
                    }
                    state = NONE_STATE;
                    if (!feof(file)) {
                        c = fgetc(file);
                        break;
                    }
                    else {
                        state = END_STATE;
                    }
                }
            case (CHAR_STATE):
                if (c == '\'') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    token->type = CHAR;
                    if (feof(file)) {
                        tokenError(first, 1);
                        return NULL;
                    }
                    c = fgetc(file);
                    pushBackVector(token->vec, c);
                    if (feof(file)) {
                        tokenError(first, 1);
                        return NULL;
                    }
                    c = fgetc(file);
                    if (c != '\'') {
                        tokenError(first, 1);
                        return NULL;
                    }
                    state = NONE_STATE;
                    if (!feof(file)) {
                        c = fgetc(file);
                    }
                    else {
                        state = END_STATE;
                    }
                    break;
                }
            case (SCOPE_STATE):
                if (c == '{' || c == '}') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    if (c == '{') {
                        pushBackVector(token->vec, '{');
                        token->type = SCOPE_OPEN;
                    }
                    else {
                        pushBackVector(token->vec, '}');
                        token->type = SCOPE_CLOSE;
                    }
                    state = NONE_STATE;
                    if (!feof(file)) {
                        c = fgetc(file);
                        break;
                    }
                }
            case (DELIMITER_STATE):
                if (c == ')' || c == '(' || c == ',' || c == ';' || c == '[' || c == ']' || c == ':') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    token->type = DELIMITER;
                    pushBackVector(token->vec, c);
                    state = NONE_STATE;
                    if (!feof(file)) {
                        c = fgetc(file);
                        break;
                    }
                }
            case (OPERATOR_STATE):
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>'
                    || c == '&' || c == '|' || c == '!' || c == '~' || c == '^') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    switch (c) {
                        case '+':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '+');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else if (c == '+') {
                                    pushBackVector(token->vec, '+');
                                    pushBackVector(token->vec, '+');
                                    token->order = 3;
                                    token->type = UNAR_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '+');
                                    token->order = 6;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '+');
                                token->order = 6;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '-':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '-');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else if (c == '-') {
                                    pushBackVector(token->vec, '-');
                                    pushBackVector(token->vec, '-');
                                    token->order = 3;
                                    token->type = UNAR_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '-');
                                    token->order = 6;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '-');
                                token->order = 6;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '*':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '*');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '*');
                                    token->order = 5;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '*');
                                token->order = 5;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '/':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '/');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '/');
                                    token->order = 5;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '/');
                                token->order = 5;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '%':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '%');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '%');
                                    token->order = 5;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '%');
                                token->order = 5;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '=':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '=');
                                    pushBackVector(token->vec, '=');
                                    token->order = 10;
                                    token->type = BIN_OPERATOR  ;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '=');
                                token->order = 16;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '<':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '<');
                                    pushBackVector(token->vec, '=');
                                    token->order = 9;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else if (c == '<') {
                                    pushBackVector(token->vec, '<');
                                    pushBackVector(token->vec, '<');
                                    token->order = 7;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                        if (c == '=') {
                                            pushBackVector(token->vec, '=');
                                            token->order = 16;
                                            token->type = BIN_OPERATOR;
                                        }
                                        if (!feof(file)) {
                                            c = fgetc(file);
                                        }
                                        else {
                                            state = END_STATE;
                                            break;
                                        }
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '<');
                                    token->order = 9;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '<');
                                token->order = 9;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '>':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '>');
                                    pushBackVector(token->vec, '=');
                                    token->order = 9;
                                    token->type = BIN_OPERATOR;
                                    if (feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                if (c == '>') {
                                    pushBackVector(token->vec, '>');
                                    pushBackVector(token->vec, '>');
                                    token->order = 7;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                        if (c == '=') {
                                            pushBackVector(token->vec, '=');
                                            token->order = 16;
                                            if (!feof(file)) {
                                                c = fgetc(file);
                                            }
                                            else {
                                                state = END_STATE;
                                            }
                                        }
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '>');
                                    token->order = 9;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '>');
                                token->order = 9;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '&':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '&') {
                                    pushBackVector(token->vec, '&');
                                    pushBackVector(token->vec, '&');
                                    token->order = 14;
                                    token->type = BIN_OPERATOR;
                                    if (feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else if (c == '=') {
                                    pushBackVector(token->vec, '&');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '&');
                                    token->order = 11;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '&');
                                token->order = 11;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '|':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '|') {
                                    pushBackVector(token->vec, '|');
                                    pushBackVector(token->vec, '|');
                                    token->order = 15;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else if (c == '=') {
                                    pushBackVector(token->vec, '|');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '>');
                                    token->order = 13;
                                    token->type = BIN_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '|');
                                token->order = 13;
                                token->type = BIN_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '!':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '!');
                                    pushBackVector(token->vec, '=');
                                    token->order = 10;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '!');
                                    token->order = 3;
                                    token->type = UNAR_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '!');
                                token->order = 3;
                                token->type = UNAR_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        case '~':
                            pushBackVector(token->vec, '~');
                            token->order = 3;
                            token->type = UNAR_OPERATOR;
                            if (!feof(file)) {
                                c = fgetc(file);
                                state = NONE_STATE;
                            }
                            else {
                                state = END_STATE;
                            }
                            break;
                        case '^':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '^');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
                                    token->type = BIN_OPERATOR;
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '^');
                                    token->order = 12;
                                    token->type = UNAR_OPERATOR;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '^');
                                token->order = 12;
                                token->type = UNAR_OPERATOR;
                                state = END_STATE;
                            }
                            break;
                        default:
                            tokenError(first, 3);
                            return first;
                    }
                }
            case (INCLUDE_STATE):
                if (c == '#') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    while(c != ' ' && !feof(file)) {
                        pushBackVector(token->vec, c);
                        c = fgetc(file);
                    }
                    while (c == ' ' && !feof(file)) {
                        c = fgetc(file);
                    }
                    token->type = INCLUDE;
                    newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    while(c != ' ' && !feof(file) && c != '\n') {
                        pushBackVector(token->vec, c);
                        c = fgetc(file);
                    }
                    c = fgetc(file);
                    state = NONE_STATE;

                }
            case (END_STATE):
                break;
            default:
                if (feof(file)) {
                    break;
                }
                tokenError(first, 4);
                return first;
        }
    }

    token = first;
    first = first->next;
    deleteToken(token);
    
    token = first;
    while (token != NULL) {
        if (token->vec != NULL) {
            pushBackVector(token->vec, '\0');
        }
        if (token->type == NONE) {
            checkKeyword(token);
        }
        token = token->next;
    }
    
    return first;
}