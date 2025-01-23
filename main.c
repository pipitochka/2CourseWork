#include "Source/Lexer/lexer.h"
//#include "Source/Errors/errors.h"

int main() {
    //printErrorMessage(1);
    Token* tokens = lexer("../test.txt");
    printTokens(tokens);
    freeTokens(tokens);
    return 0;
}
