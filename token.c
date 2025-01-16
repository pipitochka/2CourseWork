#include <string.h>
#include "token.h"

enum States {NONE_STATE, WORD_STATE, NUMBER_STATE, STRING_STATE, CHAR_STATE, SCOPE_STATE, DELIMITER_STATE};


int main() {
    FILE* file;

    Token* token = initToken(); ;
    Token* first = token;
    token->next = NULL;
    file = fopen("../test.txt", "r");

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
                if (c == ')' || c == '(' || c == ',' || c == ';') {
                    state = DELIMITER_STATE;
                    break;
                }
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
                    if (!feof(file)) {c = fgetc(file);}
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
                if (c == ')' || c == '(' || c == ',' || c == ';') {
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
            default:
                if (feof(file)) {
                    break;
                }
                exit(2);
        }
    }

    printToken(first);

    freeToken(first);
}