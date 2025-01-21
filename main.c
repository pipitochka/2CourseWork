#include "Source/Lexer/lexer.h"


int main() {
    Token* tokens = lexer("../test.txt");
    printTokens(tokens);
    freeTokens(tokens);
    return 0;
}
