#include "Source/Compiler/Lexer/include/lexer.h"
//#include "Source/Syntaxer/include/Node.h"

int main() {
    //printErrorMessage(1);
    Token* tokens = lexer("../test.txt");
    printTokens(tokens);
    freeTokens(tokens);
    //syntaxTree* q = createSyntaxTree(tokens);
    return 0;
}
