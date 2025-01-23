#include "tokenError.h"
#include "../Error/error.h"

void tokenError(Token *token, int x){
    printErrorMessage(x);
    freeTokens(token);
}
