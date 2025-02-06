#include "../include/tokenError.h"
#include "../../../Safe/Error/include/error.h"

void tokenError(Token *token, int x){
    printErrorMessage(x);
    deleteTokens(token);
}
