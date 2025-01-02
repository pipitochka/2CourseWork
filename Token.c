#include <stdio.h>
#include <stdlib.h>

//enum tokenNames {};

enum States {N, WORD, ID, NUM};

typedef struct Tok{
    //enum tokenNames type;
    char value[256];
    struct Tok* next;
} Token;

void printToken(Token* token) {
    while (token != NULL && token->next != NULL) {
        printf("%s", token->value);
        printf("\n");
        token = token->next ? token->next : NULL;
    }
}

void freeToken(Token* token) {
    if (token->next != NULL) {
        freeToken(token->next);
    }
    free(token);
}


int main() {
    char buffer[256];
    FILE* file;

    Token* token = (Token *) malloc(sizeof(Token)); ;
    Token* first = token;
    token->next = NULL;
    file = fopen("../test.txt", "r");

    enum States state = N;

    char c = fgetc(file);
    while (!feof(file)) {
        switch (state) {
            //неизвестное нечто
            case (N):
                //пустые символы
                while (c == ' ' || c == '\t' || c == '\n') {
                    c = getc(file);
                }
                //числа
                if (c >= '0' && c <= '9') {
                    state = NUM;
                    break;
                }
                //слова
                if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                    state = WORD;
                    break;
                }
                exit(1);
            case (NUM):
                if (c >= '0' && c <= '9') {
                    int t = 0;
                    while (c >= '0' && c <= '9') {
                        token->value[t] = c;
                        c = getc(file);
                        t++;
                    }
                    t++;
                    token->value[t] = '\0';
                    Token* newToken = (Token *) malloc(sizeof(Token));
                    token->next = newToken;
                    newToken->next = NULL;
                    token = newToken;
                }
                state = N;
                if (!feof(file)) {c = fgetc(file);}
                break;
            case (WORD):
                if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                    int t = 0;
                    while (c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                        token->value[t] = c;
                        c = getc(file);
                        t++;
                    }
                    t++;
                    token->value[t] = '\0';
                    Token* newToken = (Token *) malloc(sizeof(Token));
                    token->next = newToken;
                    newToken->next = NULL;
                    token = newToken;
                }
                state = N;
                if (!feof(file)) {c = fgetc(file);}
                break;
            default:
                exit(2);
        }
    }

    printToken(first);

    freeToken(first);
}