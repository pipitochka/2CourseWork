#include <string.h>
#include "token.h"

enum States {NONE_STATE, WORD_STATE, NUMBER_STATE, STRING_STATE, CHAR_STATE, SCOPE_STATE,
    DELIMITER_STATE, OPERATOR_STATE, END_STATE, INCLUDE_STATE};


Token* lexer(char* name) {
    FILE* file;

    Token* token = initToken(); ;
    Token* first = token;
    token->next = NULL;
    file = fopen(name, "r");
    if (file == NULL) {
        printf("File not found\n");
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
                printf("Error in symbol %c", c);
                exit(1);
            case (NUMBER_STATE):
                if (c >= '0' && c <= '9') {
                    Token* newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    while (!feof(file) && c >= '0' && c <= '9') {
                        pushBackVector(token->vec, c);
                        c = getc(file);
                    }
                    pushBackVector(token->vec, '\0');
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
                    pushBackVector(token->vec, '\0');
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
                        printf("error: unterminated string\n");
                        exit(1);
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
                        printf("error: unterminated character\n");
                        exit(1);
                    }
                    c = fgetc(file);
                    pushBackVector(token->vec, c);
                    if (feof(file)) {
                        printf("error: unterminated character\n");
                        exit(1);
                    }
                    c = fgetc(file);
                    if (c != '\'') {
                        printf("error: unterminated character\n");
                        exit(1);
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
                    token->type = OPERATOR;
                    switch (c) {
                        case '+':
                            if (!feof(file)) {
                                c = fgetc(file);
                                if (c == '=') {
                                    pushBackVector(token->vec, '+');
                                    pushBackVector(token->vec, '=');
                                    token->order = 16;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '+');
                                token->order = 6;
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
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else if (c == '+') {
                                    pushBackVector(token->vec, '-');
                                    pushBackVector(token->vec, '-');
                                    token->order = 3;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '-');
                                token->order = 6;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '*');
                                token->order = 5;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '/');
                                token->order = 5;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '%');
                                token->order = 5;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '=');
                                token->order = 16;
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
                                    if (feof(file)) {
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
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                        if (c == '=') {
                                            pushBackVector(token->vec, '=');
                                            token->order = 16;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '<');
                                token->order = 9;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '>');
                                token->order = 9;
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
                                    if (!feof(file)) {
                                        c = fgetc(file);
                                    }
                                    else {
                                        state = END_STATE;
                                        break;
                                    }
                                }
                                else {
                                    pushBackVector(token->vec, '>');
                                    token->order = 11;
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '&');
                                token->order = 11;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '|');
                                token->order = 13;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '!');
                                token->order = 3;
                                state = END_STATE;
                            }
                            break;
                        case '~':
                            pushBackVector(token->vec, '~');
                            token->order = 3;
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
                                }
                                state = NONE_STATE;
                                break;
                            }
                            else {
                                pushBackVector(token->vec, '^');
                                token->order = 12;
                                state = END_STATE;
                            }
                            break;
                        default:
                            printf("Invalid opertaor");
                            exit(-2);
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
                    newToken = initToken();
                    token->next = newToken;
                    token = newToken;
                    while(c != ' ' && !feof(file)) {
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
                exit(2);
        }
    }
    return first;
}